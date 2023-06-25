/* Imports */
#include "utils_common.h"       // Header file common to both kernel and user programs
#include <linux/module.h>       // For Linux modules functions
#include <linux/kernel.h>       // For debugging macros (ie KERN_* log levels)
#include <linux/init.h>         // For module initialisation functions (__init and __exit functions)
#include <linux/fs.h> 	        // For Linux file systems support
#include <linux/device.h>       // For kernel driver module support
#include <linux/slab.h>         // For in-kernel dynamic memory allocation
#include <linux/uaccess.h>      // For userspace access functions (copy_to_user() and copy_from_user())
#include <crypto/hash.h>        // For cryptographic hashing functions
#include <linux/string.h>		// For string functions

/* Global Variables */
static int dev_num;                                                         // Major number of the character device
static struct class * device_class = NULL;                                  // Device driver class pointer
static struct device * device_dev = NULL;                                   // Device driver pointer
static size_t open_count = 0;                                               // Number of types character device has been opened
static userspace_t userspace;                                               // Data from userspace
static char digest[BUF_SIZE];                                               // Result of hashing process in kernel space

/* Function Prototypes */
static int device_open(struct inode*, struct file*);                        // Function that is invoked whenever character device is opened
static int device_release(struct inode*, struct file*);                     // Function that is invoked whenever character device is closed
static ssize_t device_read(struct file*, char*, size_t, loff_t*);           // Function to read character device's contents
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);    // Function to write to character device

/* Struct Definitions */
// Struct to map local file operation functions to default system calls (reimplement default functions)
static struct file_operations fo = {
	.owner = THIS_MODULE,                                                   // Pointer to module that holding variable fo
	.open = device_open,                                                    // Remap open function
	.release = device_release,                                              // Remap release function
	.read = device_read,                                                    // Remap read function
	.write = device_write,                                                  // Remap write function
};