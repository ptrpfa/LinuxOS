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

	// Initialise variables
	int char_dev; 						// Integer to store character device's file descriptor value
	char plaintext[BUF_SIZE];			// Character array to store plaintext string
	char hash_digest[BUF_SIZE];			// Character array to store hashed string
	char hash_algorithm[TYPE_SIZE]; 	// Character array to store selected hashing algorithm
	size_t bytes_to_print = 0;			// Number of bytes to print, depending on the selected hashing algorithm

	// Open character device in kernel space (read & write mode)
	char_dev = open(CHAR_DEV_PATH, O_RDWR); 
	// Check for errors when opening character device
	if(char_dev < 0) { 
		// Print error for debugging
		perror("Failed to open the character device!\n");
		// Terminate program (abnormal termination) and return value of error 
		return errno;
	}
	else {
		// Print for debugging
		printf("Successfully opened character device!\n");
	}
	
	// Get plaintext from user's input
	printf("Enter a string > ");
	// Check for errors when getting user's input
	if(fgets(plaintext, BUF_SIZE, stdin) == NULL) {
		// Print error for debugging
		printf("Error while getting plaintext!\n");
		// Terminate program (abnormal termination)
		return -1;
	}

	// Get hashing algorithm from user's input
	printf("Select a hashing algorithm (MD5, SHA1, SHA256, SHA384, SHA512) > ");
	// Check for errors when getting user's input
	if(fgets(hash_algorithm, TYPE_SIZE, stdin) == NULL) {
		// Print error for debugging
		printf("Error while getting hashing algorithm!\n");
		// Terminate program (abnormal termination)
		return -1;
	}

	// Remove trailing newline delimiting character
	strtok(plaintext, "\n");
	strtok(hash_algorithm, "\n");

	// Loop through each character of hash algorithm array
	for(char* p = hash_algorithm; *p; p++) {
		// Turn each character to uppercase
		*p = toupper((unsigned char)*p);
	}

	// Initialise an instance of the custom userspace struct (custom struct used to pass two parameters to kernel module)
	userspace_t u;

	// Set plaintext value of userspace struct
	strncpy((char*)u.plaintext, plaintext, BUF_SIZE);

	// Set hashing algorithm value of userspace struct
	if(!strcmp(hash_algorithm, "MD5")) {
		// Set algorithm to MD5
		u.algorithm = MD5;
		// Read 16 bytes for MD5 hashes
		bytes_to_print = 16;
	}
	else if(!strcmp(hash_algorithm, "SHA1")) {
		// Set algorithm to SHA1
		u.algorithm = SHA1;
		// Read 20 bytes for SHA1 hashes
		bytes_to_print = 20;
	}
	else if(!strcmp(hash_algorithm, "SHA256")) {
		// Set algorithm to SHA256
		u.algorithm = SHA256;
		// Read 32 bytes for SHA256 hashes
		bytes_to_print = 32;
	}
	else if(!strcmp(hash_algorithm, "SHA384")) {
		// Set algorithm to SHA384
		u.algorithm = SHA384;
		// Read 48 bytes for SHA384 hashes
		bytes_to_print = 48;
	}
	else if(!strcmp(hash_algorithm, "SHA512")) {
		// Set algorithm to SHA512
		u.algorithm = SHA512;
		// Read 64 bytes for SHA512 hashes
		bytes_to_print = 64;
	}
	else {
		// Print error for debugging
		printf("Selected hashing algorithm is not supported!\n");
		// Terminate program (abnormal termination)
		return -1;
	}

	// Write userspace struct from the user space to the character device in the kernel space
	if(write(char_dev, &u, sizeof(userspace_t)) < 0) {
		// Print error for debugging
		perror("Error when writing data from the user space to the kernel space!");
		// Terminate program (abnormal termination) and return value of error 
		return errno;
	} 

	// Read from character device
	if(read(char_dev, hash_digest, BUF_SIZE) < 0) {
		// Print error for debugging
		perror("Error when reading data from the kernel space!");
		// Terminate program (abnormal termination) and return value of error 
		return errno;
	}

	// Print results
	printf("Plaintext received: %s\nHashing Algorithm: %s\nHash: ", u.plaintext, hash_algorithm);
	// Loop through each byte of hash digest and print the results
	for(size_t i = 0; i < bytes_to_print; i++) {
		printf("%02x", (unsigned char)hash_digest[i]);	
	}
	printf("\n");
	
    // End of program
	return 0;

}