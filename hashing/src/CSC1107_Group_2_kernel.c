// Import custom header file
#include "header/utils_kernel.h" 

// File operation struct
// Map local functions to default system calls (reimplement default functions)
static struct file_operations fo = {
	.owner = THIS_MODULE,
	.open = hashkm_open,
	.release = hashkm_close,
	.read = hashkm_read,
	.write = hashkm_write,
};

/* Functions */
// Module Entrypoint: Function upon module entry
static int __init hashkm_init(void) {
	pr_info("%s: Loading, please wait...\n", DEV_NAME);
	
	// Get a new major number for the character device
	dev_num = register_chrdev(0, DEV_NAME, &fo);
	if(dev_num < 0) { // Check errors
		pr_alert("%s: Error while trying to register major number\n", DEV_NAME);
		return dev_num;
	}

	pr_info("%s: New device successfully registered(major number: %d)\n", DEV_NAME, dev_num);
	
	// Register device class
	hashkm_class = class_create(THIS_MODULE, DEV_CLASS);
	if(IS_ERR(hashkm_class)) { // Check errors
		unregister_chrdev(dev_num, DEV_NAME); // Unregister device major number
		pr_alert("%s: unable to register device class\n", DEV_NAME);
		return PTR_ERR(hashkm_class);
	}
	pr_info("%s: Device class successfully register\n", DEV_NAME);

	// Register character device
	hashkm_dev = device_create(hashkm_class, NULL, MKDEV(dev_num, 0), NULL, DEV_NAME);
	if(IS_ERR(hashkm_dev)) {  // Check errors
		class_destroy(hashkm_class);  // Destroy device class
		unregister_chrdev(dev_num, DEV_NAME); // Unregister device major number
		pr_alert("%s: failed to create a new device\n", DEV_NAME);
		return PTR_ERR(hashkm_dev);
	}
	
	pr_info("%s: device driver successfully created\n", DEV_NAME);

	return 0;
}

// Module Exit: Function upon module removal 
static void __exit hashkm_exit(void) {
	device_destroy(hashkm_class, MKDEV(dev_num, 0)); // Remove device
	class_unregister(hashkm_class); // Unregister the class
	class_destroy(hashkm_class); // Destroy the class
	unregister_chrdev(dev_num, DEV_NAME); // Unregister device major number
	pr_info("%s: module successfully unloaded\n", DEV_NAME);
}

/* This function is invoked each time an userspace process
 * tries to open the character device. It is usually being 
 * used to set up the environment for the rest of the module but
 * since we do not have anything to configure, we will just
 * print out a message */
static int hashkm_open(struct inode * inodep, struct file * filep) {
	pr_info("%s: This device has been opened %d time(s)\n", DEV_NAME, (int)++open_count);

	return 0;
}

/* This function is invoked each time an userspace process
 * closes/releases the character device. It is usually being used
 * to free allocated resources but since we have not anything
 * to do, we will just print out a message */
static int hashkm_close(struct inode * inodep, struct file * filep) {
	pr_info("%s: device closed successfully\n", DEV_NAME);

	return 0;
}

/* This function is invoked each time we call the 'read()' syscall
 * from userspace. In our module, we will use the function 
 * 'copy_to_user' to send back to the user the result(i.e., the hashed string) 
 
	Send data to userspace each time a user process uses the read() syscall
 */
static ssize_t hashkm_read(struct file * filep, char * buffer, size_t len, loff_t * offset) {
	size_t bytes_not_copied = 0;
	// 16 bytes for MD5, 20 byes for SHA1, 32 bytes for SHA256
	size_t bytes_to_copy = (userspace.algorithm == SHA256) ? 32 : (userspace.algorithm == SHA1 ? 20 : 16);

	// copy_to_user returns 0 on success while it returns
	// the number of bytes not copied on errors
	// copy_to_user(to, from, no of bytes)
	bytes_not_copied = copy_to_user(buffer, digest, bytes_to_copy);
	if(bytes_not_copied) { // Check errors
		pr_warn("%s: Failed to send result to userspace\n", DEV_NAME);
		return -EFAULT;
	}

	return 0;
}


/* This function is invoked each time we call the 'write()' syscall
 * from userspace. In our module, we will use the function 'write_to_user'
 * to retrieve user data. We will then hash the plaintext string according to 
 * the chosen algorithm using Linux cryptographic APIs 
 
	Read input string and algorithm choic from userspace using write() syscall
 */
static ssize_t hashkm_write(struct file * filep, const char * buffer, size_t len, loff_t * offset) {
	size_t bytes_not_copied = 0;
	struct crypto_shash* algorithm;
	struct shash_desc* desc;
	int err;

	// 'copy_from_user' method returns 0 on success and the number of bytes not copied
	// on error
	// copy_from_user(to, from, no of bytes)
	bytes_not_copied = copy_from_user(&userspace, buffer, sizeof(userspace_t));
	if(bytes_not_copied) { // Check errors
		pr_warn("%s: error while copying %zu bytes from userspca\n", DEV_NAME, bytes_not_copied);
		return -EFAULT;
	}

	// Select hashing algorithm
	switch(userspace.algorithm) {
		case MD5: algorithm = crypto_alloc_shash("md5", 0, 0); break;
		case SHA1: algorithm = crypto_alloc_shash("sha1", 0, 0); break;
		case SHA256: algorithm = crypto_alloc_shash("sha256", 0, 0); break;
		default: pr_alert("%s: hashing algorithm not recognized\n", DEV_NAME); return -EFAULT;
	}

	// Check if selected algorithm is available in the system
	if(IS_ERR(algorithm)) { // Check errors
		pr_alert("%s: Hashing algorithm not supported\n", DEV_NAME);
		return -EFAULT;
	}


	desc = kmalloc(sizeof(struct shash_desc) + crypto_shash_descsize(algorithm), GFP_KERNEL);
	if(!desc) { // check errors
		pr_err("%s: failed to allocate memory(kmalloc)\n", DEV_NAME);
		return -ENOMEM;
	}
	desc->tfm = algorithm;

	// Initialize shash API
	err = crypto_shash_init(desc);
	if(err)  {
		pr_err("%s: failed to initialize shash\n", DEV_NAME);
		goto out;
	}

	// Execute hash function
	err = crypto_shash_update(desc, userspace.plaintext, strlen(userspace.plaintext));
	if(err) {
		pr_err("%s: failed to execute hashing function\n", DEV_NAME);
		goto out;
	}

	// Write the result to a new char buffer
	err = crypto_shash_final(desc, digest);
	if(err) {
		pr_err("%s: Failed to complete hashing function\n", DEV_NAME);
		goto out;
	}

	// Finally, clean up resources
	crypto_free_shash(algorithm);
	kfree(desc);

	pr_info("%s: String successfully hashed. Read from this device to get the result\n", DEV_NAME);

	return 0;

out: // Manage errors
	crypto_free_shash(algorithm);
	kfree(desc);
	return err;
}

/* Module Specifications */
// Module information
MODULE_LICENSE("Dual BSD/GPL");                  	    // Module license
MODULE_AUTHOR("Group 2 CSC1107 Operating Systems");     // Module author
MODULE_VERSION("1");                  	                // Module version number
MODULE_DESCRIPTION("Linux Kernel module for Q1");       // Module description

// Register module entry and exit points
module_init(hashkm_init);
module_exit(hashkm_exit);