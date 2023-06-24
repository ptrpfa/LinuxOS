/* Client user-space program */
// Import custom header file
#include "header/utils_user.h" 

// Program entrypoint
int main(void) {

	// Get user's option
    // int user_option = 0;

    // Read current date and time and return
    // It is 18:36:22 on 18th May 2023 now

    // Calculate hash value of sentence 
    // 

	int dev, ret;
	char digest[BUF_SIZE];

	// Open the device
	printf("Opening character device, wait please...");
	dev = open(CHAR_DEV_PATH, O_RDWR); // Open the device in read and write mode
	if(dev < 0) { // Handle errors
		perror("Failed to open the device");
		return errno;
	}
	
	// Read the plaintext from stdin
	char plaintext[BUF_SIZE];
	printf("Insert a string: ");
	if(fgets(plaintext, sizeof(plaintext), stdin) == NULL) {
		printf("Error while reading from stdin");
		return -1;
	}

	// Read the hashing algorithm from stdin
	char type[8];
	printf("Choose a hashing algorith(MD5,SHA1,SHA256): ");
	if(fgets(type, sizeof(type), stdin) == NULL) {
		printf("Error while reading from stdin");
		return -1;
	}

	// Parse string using newline as delimiter
	strtok(plaintext, "\n");
	strtok(type, "\n");
	for(char* p = type; *p; ++p) {
		*p = toupper((unsigned char)*p);
	}

	// Create an userspace struct
	userspace_t u;
	strncpy((char*)u.plaintext, plaintext, BUF_SIZE);
	if(!strcmp(type, "MD5")) u.algorithm = MD5;
	else if(!strcmp(type, "SHA1")) u.algorithm = SHA1;
	else if(!strcmp(type, "SHA256")) u.algorithm = SHA256;
	else if(!strcmp(type, "SHA384")) u.algorithm = SHA384;
	else if(!strcmp(type, "SHA512")) u.algorithm = SHA512;
	else {
		printf("Algorithm not supported");
		return -1;
	}

	// Write to device
	printf("Sending data to kernel, wait please...");
	ret = write(dev, &u, sizeof(userspace_t));
	if(ret < 0) {
		perror("Error while sending data to kernel space");
		return errno;
	}

	// Read from device
	ret = read(dev, digest, BUF_SIZE);
	if(ret < 0) {
		perror("Error while reading data from kernel space");
		return errno;
	}

	// Initialise number of bytes to print, depending on the selected hashing algorithm
	size_t bytes_to_print;
	if(u.algorithm == MD5) {
		// Read 16 bytes for MD5 hashes
		bytes_to_print = 16;
	}
	else if(u.algorithm == SHA1) {
		// Read 20 bytes for SHA1 hashes
		bytes_to_print = 20;
	}
	else if(u.algorithm == SHA256) {
		// Read 32 bytes for SHA256 hashes
		bytes_to_print = 32;
	}
	else if(u.algorithm == SHA384) {
		// Read 48 bytes for SHA384 hashes
		bytes_to_print = 48;
	}
	else if(u.algorithm == SHA512) {
		// Read 64 bytes for SHA512 hashes
		bytes_to_print = 64;
	}
	else {
		// Read zero bytes upon no matching hashing algorithm
		bytes_to_print = 0;
	}

	printf("Original string: \"%s\", %s digest: \"", u.plaintext, type);
	for(size_t i = 0; i < bytes_to_print; i++)
		printf("%02x", (unsigned char)digest[i]);
	printf("\"");
	
	return 0;

}