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

/* Global Variables */

/* Function Prototypes */
