/* Client user-space program */
// Import custom header file
#include "header/utils_user.h" 

// Program entrypoint
int main(void) {

	// Initialise base variables
	userspace_t u; 						// Initialise an instance of the custom userspace struct (custom struct used to pass multiple parameters to kernel module)
	int char_dev; 						// Integer to store character device's file descriptor value
	char* plaintext;					// Character pointer to store plaintext string
	char hash_algorithm[TYPE_SIZE]; 	// Character array to store selected hashing algorithm
	size_t hash_digest_bytes = 0;		// Number of bytes allocated for hash digest (varies according to hashing algorithm used)

	// Get plaintext datetime string
	plaintext = get_datetime_string();
	if(plaintext == NULL) {	// Check for errors when getting datetime string
		// Print error for debugging
		printf("Error when getting datetime string!\n");
		// Terminate program (abnormal termination)
		return -1;
	}	
	else {
		// Print for debugging
		printf("Original Sentence: %s\n", plaintext);
		// Set plaintext value of userspace struct
		strncpy((char*)u.plaintext, plaintext, BUF_SIZE);
	}

	// Get selected hashing algorithm from user's input
	printf("Select a hashing algorithm (MD5, SHA1, SHA256, SHA384, SHA512): ");
	// Check for errors when getting user's input
	if(fgets(hash_algorithm, TYPE_SIZE, stdin) == NULL) {
		// Print error for debugging
		printf("Error while getting hashing algorithm!\n");
		// Terminate program (abnormal termination)
		return -1;
	}
	else {
		// Remove trailing newline delimiting character
		strtok(hash_algorithm, "\n");
		
		// Loop through each character of selected hash algorithm
		for(char* p = hash_algorithm; *p; p++) {
			// Turn each character to uppercase
			*p = toupper((unsigned char)*p);
		}

		// Check hashing algorithm used
		if(!strcmp(hash_algorithm, "MD5")) {
			// Set hashing algorithm value of userspace struct to MD5
			u.algorithm = HASH_MD5;
			// Read 16 bytes for MD5 hashes
			hash_digest_bytes = 16;
		}
		else if(!strcmp(hash_algorithm, "SHA1")) {
			// Set hashing algorithm value of userspace struct to SHA1
			u.algorithm = HASH_SHA1;
			// Read 20 bytes for SHA1 hashes
			hash_digest_bytes = 20;
		}
		else if(!strcmp(hash_algorithm, "SHA256")) {
			// Set hashing algorithm value of userspace struct to SHA256
			u.algorithm = HASH_SHA256;
			// Read 32 bytes for SHA256 hashes
			hash_digest_bytes = 32;
		}
		else if(!strcmp(hash_algorithm, "SHA384")) {
			// Set hashing algorithm value of userspace struct to SHA384
			u.algorithm = HASH_SHA384;
			// Read 48 bytes for SHA384 hashes
			hash_digest_bytes = 48;
		}
		else if(!strcmp(hash_algorithm, "SHA512")) {
			// Set hashing algorithm value of userspace struct to SHA512
			u.algorithm = HASH_SHA512;
			// Read 64 bytes for SHA512 hashes
			hash_digest_bytes = 64;
		}
		else {
			// Print error for debugging
			printf("Selected hashing algorithm is not supported!\n");
			// Terminate program (abnormal termination)
			return -1;
		}
	}

	// Initialise variables to store hash
	unsigned char user_hash_digest[hash_digest_bytes]; 		// Character array to store user space hashed string
	char kernel_hash_digest[hash_digest_bytes]; 			// Character array to store kernel space hashed string

	/* User-Space Hashing */
	// Check hashing algorithm used and compute user space hash
	if(!strcmp(hash_algorithm, "MD5")) {
		// Compute MD5 hash
		compute_md5_hash(plaintext, strlen(plaintext), user_hash_digest);		
	}
	else if(!strcmp(hash_algorithm, "SHA1")) {
		// Compute SHA1 hash
		compute_sha1_hash(plaintext, strlen(plaintext), user_hash_digest);
	}
	else if(!strcmp(hash_algorithm, "SHA256")) {
		// Compute SHA256 hash
		compute_sha256_hash(plaintext, strlen(plaintext), user_hash_digest);
	}
	else if(!strcmp(hash_algorithm, "SHA384")) {
		// Compute SHA384 hash
		compute_sha384_hash(plaintext, strlen(plaintext), user_hash_digest);
	}
	else if(!strcmp(hash_algorithm, "SHA512")) {
		// Compute SHA512 hash
        compute_sha512_hash(plaintext, strlen(plaintext), user_hash_digest);
	}
	// Set user hash digest value of userspace struct
	memcpy(u.user_hash_digest, user_hash_digest, hash_digest_bytes);

	// Open character device in kernel space (read & write mode)
	char_dev = open(CHAR_DEV_PATH, O_RDWR); 
	// Check for errors when opening character device
	if(char_dev < 0) { 
		// Print error for debugging
		perror("Failed to open the character device!\n");
		// Terminate program (abnormal termination) and return value of error 
		return errno;
	}

	// Write userspace struct from the user space to the character device in the kernel space
	if(write(char_dev, &u, sizeof(userspace_t)) < 0) {
		// Print error for debugging
		perror("Error when writing data from the user space to the kernel space!");
		// Terminate program (abnormal termination) and return value of error 
		return errno;
	} 

	// Read from character device
	if(read(char_dev, kernel_hash_digest, BUF_SIZE) < 0) {
		// Print error for debugging
		perror("Error when reading data from the kernel space!");
		// Terminate program (abnormal termination) and return value of error 
		return errno;
	}

	// Print results
	printf("Plaintext received: %s\nHashing Algorithm: %s\nKernel Hash: ", u.plaintext, hash_algorithm);
	// Loop through each byte of hash digest and print the results
	for(size_t i = 0; i < hash_digest_bytes; i++) {
		printf("%02x", (unsigned char)kernel_hash_digest[i]);	
	}
	printf("\nUser Hash: ");
	// Loop through each byte of hash digest and print the results
	for(size_t i = 0; i < hash_digest_bytes; i++) {
		printf("%02x", (unsigned char)user_hash_digest[i]);	
	}
	printf("\n");
    // End of program
	free(plaintext);		// Free dynamically allocated memory for plaintext string
	return 0;				// Normal program termination

}