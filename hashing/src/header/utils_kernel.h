/* Imports */
#include "utils_common.h"	// Header file common to both kernel and user programs
#include <linux/module.h>   // For Linux modules functions
#include <linux/kernel.h>   // For debugging macros (ie KERN_* log levels)
#include <linux/init.h>     // For module initialisation functions (__init and __exit functions)
#include <linux/fs.h> 		// For Linux file systems support
#include <linux/device.h> 	// For kernel driver module support
#include <linux/slab.h> 	// For in-kernel dynamic memory allocation
#include <linux/uaccess.h> 	// For userspace access functions (copy_to_user() and copy_from_user())
#include <crypto/hash.h> 	// For cryptographic hashing functions

/* Global Variables */
static int dev_num; 						// Major number of the character device
static struct class * hashkm_class = NULL; 	// Device driver class pointer
static struct device * hashkm_dev = NULL; 	// Device driver pointer
static size_t open_count = 0; 				// Number of types this device has been opened
static userspace_t userspace; 				// Data from userspace
static char digest[BUF_SIZE]; 				// Result of hashing process

/* Function Prototypes */
static int hashkm_open(struct inode*, struct file*);
static int hashkm_close(struct inode*, struct file*);
static ssize_t hashkm_read(struct file*, char*, size_t, loff_t*);
static ssize_t hashkm_write(struct file*, const char*, size_t, loff_t*);