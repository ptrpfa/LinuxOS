#ifndef MY_FUNCTIONS_H   // Include guard
#define MY_FUNCTIONS_H

#include <stdio.h>  // Includes other header files needed

// Structure definitions
typedef struct {
    int arrivalTime;
} Processes;

// Function prototypes
int assignA(Processes process[], int a, int num);
int assignB(Processes process[], int b, int num);

#endif /* MY_FUNCTIONS_H */