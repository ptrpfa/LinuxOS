/* Imports */
#define USER_SPACE 1        // Macro for conditional imports in custom header file
#include "utils_common.h"   // Header file common to both kernel and user programs
#include <stdio.h>          // For standard input/output functions
#include <stdlib.h>         // For general purpose functions
#include <string.h>         // For string functions
#include <unistd.h>         // For access to POSIX OS APIs
#include <errno.h>          // For error codes
#include <fcntl.h>          // For file descriptors and control operations
#include <ctype.h>          // For character manipulation functions
#include <time.h>           // For time functions
#include <openssl/md5.h>    // For hashing functions
#include <openssl/sha.h>    // For hashing functions

/* Function Definitions */
// Function to get datetime string
char* get_datetime_string(void) {

    // Initialise datetime variables
    char* str_datetime = malloc(BUF_SIZE * sizeof(char));       // Variable for overall datetime string
    char str_date[BUF_SIZE] = "";                               // Temporary variable for last portion of datetime string
    char* day_suffix;                                           // Temporary variable for day suffix portion of datetime string

    // Check for errors during memory allocation
    if (str_datetime == NULL) { 
        // Print for debugging
        printf("Memory allocation failed.\n");
        // Immediately return default datetime string
        return NULL;
    }

    // Initialise current time
    time_t t = time(NULL);

    // Get pointer to time structure (defined in time.h)
    struct tm *ptr_tm = localtime(&t);
    if (ptr_tm == NULL) {   // Check for errors
        // Print for debugging
        printf("The localtime() function failed.\n");
        // Immediately return default datetime string
		return NULL;
    }

    // Initialise day suffix
    switch (ptr_tm->tm_mday % 10) {
        case 1: 
            day_suffix = "st";
            break;
        case 2: 
            day_suffix = "nd";
            break;
        case 3: 
            day_suffix = "rd";
            break;
        default: 
            day_suffix = "th";
            break;
    }

    // Format datetime string
    strftime(str_datetime, 1024, "It is %H:%M:%S on %e", ptr_tm);   // Get initial portion of string (It is HH:MM:SS on DD)
    strftime(str_date, 1024, " %b %Y now.", ptr_tm);                // Get last portion of string ( MMM YYYY now)
    strcat(str_datetime, day_suffix);                               // Concatenate initial portion with day suffix
    strcat(str_datetime, str_date);                                 // Concatenate combined string with last portion
    
    // Return formatted datetime string
    return str_datetime;
    
}

// User space function to get MD5 hash for a given string
void compute_md5_hash(const char* input, size_t input_len, unsigned char* output) {
    MD5_CTX ctx;                            // Set context to be MD5
    MD5_Init(&ctx);                         // Initialise MD5 context
    MD5_Update(&ctx, input, input_len);     // Update MD5 context with input variable
    MD5_Final(output, &ctx);                // Finalise hash and store in output variable
}

// User space function to get SHA1 hash for a given string
void compute_sha1_hash(const char* input, size_t input_len, unsigned char* output) {
    SHA_CTX ctx;                            // Set context to be SHA1
    SHA1_Init(&ctx);                        // Initialise SHA1 context
    SHA1_Update(&ctx, input, input_len);    // Update SHA1 context with input variable
    SHA1_Final(output, &ctx);               // Finalise hash and store in output variable
}

// User space function to get SHA256 hash for a given string
void compute_sha256_hash(const char* input, size_t input_len, unsigned char* output) {
    SHA256_CTX ctx;                         // Set context to be SHA256
    SHA256_Init(&ctx);                      // Initialise SHA256 context
    SHA256_Update(&ctx, input, input_len);  // Update SHA256 context with input variable
    SHA256_Final(output, &ctx);             // Finalise hash and store in output variable
}

// User space function to get SHA384 hash for a given string
void compute_sha384_hash(const char* input, size_t input_len, unsigned char* output) {
    SHA512_CTX ctx;                         // Set context to be SHA512 (context structure of SHA-384 and SHA-512 in OpenSSL is the same)
    SHA384_Init(&ctx);                      // Initialise SHA384 context
    SHA384_Update(&ctx, input, input_len);  // Update SHA384 context with input variable
    SHA384_Final(output, &ctx);             // Finalise hash and store in output variable
}

// User space function to get SHA512 hash for a given string
void compute_sha512_hash(const char* input, size_t input_len, unsigned char* output) {
    SHA512_CTX ctx;                         // Set context to be SHA512 
    SHA512_Init(&ctx);                      // Initialise SHA512 context
    SHA512_Update(&ctx, input, input_len);  // Update SHA512 context with input variable
    SHA512_Final(output, &ctx);             // Finalise hash and store in output variable
}