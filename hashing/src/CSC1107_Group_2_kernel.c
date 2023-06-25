/* Hash module kernel program */
// Import custom header file
#include "header/utils_kernel.h" 

/* Functions */
// Module Entrypoint: Function is invoked upon module entry
static int __init device_init(void) {
	// Get character device's major number
	pr_info("%s: [1/4] Loading kernel module..\n", DEV_NAME);											// Print to kernel ring buffer for debugging
	dev_num = register_chrdev(0, DEV_NAME, &fo);														// Register character device to get its major number
	if(dev_num < 0) { 																					// Check for errors when getting character device's major number
		pr_alert("%s: Error while trying to register major number.\n", DEV_NAME);						// Print to kernel ring buffer for debugging
		return dev_num;																					// Return error code
	}
	pr_info("%s: [2/4] New device successfully registered.. (major number: %d)\n", DEV_NAME, dev_num); 	// Print to kernel ring buffer for debugging
	
	// Register device class
	device_class = class_create(THIS_MODULE, DEV_CLASS);												// Register device class
	if(IS_ERR(device_class)) { 																			// Check for errors when registering device class 
		unregister_chrdev(dev_num, DEV_NAME); 															// Unregister character device's major number upon error
		pr_alert("%s: Unable to register device class.\n", DEV_NAME);									// Print to kernel ring buffer for debugging
		return PTR_ERR(device_class);																	// Return error code
	}
	pr_info("%s: [3/4] Device class successfully registered..\n", DEV_NAME); 							// Print to kernel ring buffer for debugging

	// Register character device
	device_dev = device_create(device_class, NULL, MKDEV(dev_num, 0), NULL, DEV_NAME);					// Register character device
	if(IS_ERR(device_dev)) {  																			// Check for errors when registering character device
		class_destroy(device_class);  																	// Destroy device class upon error
		unregister_chrdev(dev_num, DEV_NAME); 															// Unregister character device's major number upon error
		pr_alert("%s: Failed to create a new device\n", DEV_NAME);										// Print to kernel ring buffer for debugging
		return PTR_ERR(device_dev);																		// Return error code
	}
	pr_info("%s: [4/4] Device driver successfully created!\n", DEV_NAME); 								// Print to kernel ring buffer for debugging

    // Return status of module initialisation
	return 0;
}

// Module Exit: Function is invoked upon module removal 
static void __exit device_exit(void) {
	device_destroy(device_class, MKDEV(dev_num, 0)); 													// Remove character device
	class_unregister(device_class); 																	// Unregister device class
	class_destroy(device_class);													 					// Destroy device class
	unregister_chrdev(dev_num, DEV_NAME); 																// Unregister character device's major number
	pr_info("%s: Module successfully unloaded!\n", DEV_NAME);											// Print to kernel ring buffer for debugging
}

// Function is invoked whenever a user space program opens the character device (used to setup environment for module)
static int device_open(struct inode * inodep, struct file * filep) {
	// Print to kernel ring buffer for debugging
	pr_info("%s: Character device has been opened %d time(s)!\n", DEV_NAME, (int)++open_count);
    // Return status of opening character device
	return 0;
}

// Function is invoked whenever a user space program close/release the character device (used to free allocated resources from module)
static int device_release(struct inode * inodep, struct file * filep) {
	// Print to kernel ring buffer for debugging
	pr_info("%s: Device closed successfully!\n", DEV_NAME);
    // Return status of closing character device
	return 0;
}

// Function is invoked whenever a user space program calls the read() system call from the user space (read data from kernel space to user space)
static ssize_t device_read(struct file * filep, char * buffer, size_t len, loff_t * offset) {
	// Initialise number of bytes to read, depending on the selected hashing algorithm
	size_t bytes_to_read;
	if(userspace.algorithm == MD5) {
		// Read 16 bytes for MD5 hashes
		bytes_to_read = 16;
	}
	else if(userspace.algorithm == SHA1) {
		// Read 20 bytes for SHA1 hashes
		bytes_to_read = 20;
	}
	else if(userspace.algorithm == SHA256) {
		// Read 32 bytes for SHA256 hashes
		bytes_to_read = 32;
	}
	else if(userspace.algorithm == SHA384) {
		// Read 48 bytes for SHA384 hashes
		bytes_to_read = 48;
	}
	else if(userspace.algorithm == SHA512) {
		// Read 64 bytes for SHA512 hashes
		bytes_to_read = 64;
	}
	else {
		// Read zero bytes upon no matching hashing algorithm
		bytes_to_read = 0;
	}

	// Read hash results from character device (read data from kernel space to user space)
	if(copy_to_user(buffer, digest, bytes_to_read)) { // Check for errors during read operation
		// Print to kernel ring buffer for debugging
		pr_warn("%s: Failed to send hash result to userspace\n", DEV_NAME);
		// Return value of error condition
		return -EFAULT;
	}
	else {
		// Print to kernel ring buffer for debugging
		pr_info("%s: Successfully read hash result from character device!\n", DEV_NAME);
    	// Return status of read from character device
		return 0;
	}
}

// Function is invoked whenever a user space program calls the write() system call from the user space (write data from user space to kernel space)
static ssize_t device_write(struct file * filep, const char * buffer, size_t len, loff_t * offset) {
	// Initialise variables
	size_t bytes_not_read = 0;		// Variable to track number of bytes that are not read successfully from the user space
	struct crypto_shash* algorithm;	// Pointer to hashing algorithm struct
	struct shash_desc* desc;		// Pointer to hashing descriptor struct
	int err = 0;					// Variable to store error value, if any

	// Read bytes from user space (read data from user space to kernel space)
	bytes_not_read = copy_from_user(&userspace, buffer, sizeof(userspace_t));
	if(bytes_not_read) { // Check for errors during read operation
		// Print to kernel ring buffer for debugging
		pr_warn("%s: Error while copying %zu bytes from user space\n", DEV_NAME, bytes_not_read);
		// Return value of error condition
		return -EFAULT;
	}

	// Initialise value of hashing algorithm
	switch(userspace.algorithm) {
		case MD5:
			algorithm = crypto_alloc_shash("md5", 0, 0);
			break;
		case SHA1:
			algorithm = crypto_alloc_shash("sha1", 0, 0);
			break;
		case SHA256:
			algorithm = crypto_alloc_shash("sha256", 0, 0);
			break;
		case SHA384:
			algorithm = crypto_alloc_shash("sha384", 0, 0);
			break;
		case SHA512:
			algorithm = crypto_alloc_shash("sha512", 0, 0);
			break;
		default: 
			// Print to kernel ring buffer for debugging
			pr_alert("%s: Hashing algorithm not recognized!\n", DEV_NAME); 
			// Return value of error condition
			return -EFAULT;
	}

	// Check if selected algorithm is available on the system
	if(IS_ERR(algorithm)) { // Check for errors
		// Print to kernel ring buffer for debugging
		pr_alert("%s: Hashing algorithm not supported\n", DEV_NAME);
		// Return value of error condition
		return -EFAULT;
	}

	// Initialise hashing descriptor struct by dynamically allocating a specified amount of space in the kernel's memory pool
	desc = kmalloc(sizeof(struct shash_desc) + crypto_shash_descsize(algorithm), GFP_KERNEL);
	if(!desc) { // Check for errors
		// Print to kernel ring buffer for debugging
		pr_err("%s: Failed to allocate memory in kernel(kmalloc)\n", DEV_NAME);
		// Return value of error condition
		return -ENOMEM;
	}
	// Assign selected hashing algorithm to hashing descriptor's cryptographic transformation 
	desc->tfm = algorithm;

	// Initialize shash API 
	err = crypto_shash_init(desc);
	if(err) {	// Check for errors during initialisation
		// Print to kernel ring buffer for debugging
		pr_err("%s: Failed to initialize shash\n", DEV_NAME);
		// Jump code execition to predefined area for handling errors that occur during the hashing process
		goto out;
	}

	// Execute hash function
	err = crypto_shash_update(desc, userspace.plaintext, strlen(userspace.plaintext));
	if(err) {	// Check for errors during hashing
		// Print to kernel ring buffer for debugging
		pr_err("%s: Failed to execute hashing function\n", DEV_NAME);
		// Jump code execition to predefined area for handling errors that occur during the hashing process
		goto out;
	}

	// Write the result to a new char buffer
	err = crypto_shash_final(desc, digest);
	if(err) {	// Check for errors during end of hashing
		// Print to kernel ring buffer for debugging
		pr_err("%s: Failed to complete hashing function\n", DEV_NAME);
		// Jump code execition to predefined area for handling errors that occur during the hashing process
		goto out;
	}

	// Free shash API
	crypto_free_shash(algorithm);
	// Free dynamically allocated space in kernel memory pool
	kfree(desc);
	// Print to kernel ring buffer for debugging
	pr_info("%s: String successfully hashed. Read from this device to get the result!\n", DEV_NAME);

	// Return status of write to character device
	return 0;

	// Predefined area for handling errors that occur during the hashing process 
	out: 
		// Free shash API
		crypto_free_shash(algorithm);
		// Free dynamically allocated space in kernel memory pool
		kfree(desc);
		// Return value of error condition
		return err;
		
}

/* Module Specifications */
// Module information
MODULE_LICENSE("Dual BSD/GPL");                  	    // Module license
MODULE_AUTHOR("Group 2 CSC1107 Operating Systems");     // Module author
MODULE_VERSION("1");                  	                // Module version number
MODULE_DESCRIPTION("Linux Kernel module for Q1");       // Module description

// Register module entry and exit points
module_init(device_init);
module_exit(device_exit);