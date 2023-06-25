/* Imports */
// Conditional import depending on program type (user or kernel)
#ifdef USER_SPACE
    #include <stdint.h>                             // For uint8_t
#else
    #include <linux/types.h>                        // For u8 and definition of custom datatypes
#endif

/* Macro Definitions */
// Character Device
#define DEV_FOLDER "/dev/"                          // Device folder
#define DEV_NAME "CSC1107OS_02_CHARDEV"             // Name of the character device
#define DEV_CLASS "CSC1107OS_02_CHARDEV_CLASS"      // Name of the device class
#define CHAR_DEV_PATH DEV_FOLDER DEV_NAME           // Formulated character device path

// Buffer size
#define BUF_SIZE 1024                               // Size of plaintext buffer (1MB)
#define TYPE_SIZE 8                                 // Size of hash type (8 bytes)

/* Type & Struct Definitions */
// Conditional type definition depending on program type (user or kernel)
#ifdef USER_SPACE
    typedef uint8_t custom_unsigned_integer;
#else
    typedef u8 custom_unsigned_integer;
#endif

// Type definition of different enumerated hash types
typedef enum hash {	MD5, SHA1, SHA256, SHA384, SHA512 } hash_t;

// Custom struct used to pass two parameters to kernel module
typedef struct userspace {
	custom_unsigned_integer plaintext[BUF_SIZE];
	hash_t algorithm;
} userspace_t;