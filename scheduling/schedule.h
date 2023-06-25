#ifndef MY_FUNCTIONS_H   // Include guard
#define MY_FUNCTIONS_H

#include <stdio.h>  // Includes other header files needed
#include <limits.h>

// Structure definitions
typedef struct{
    int processId;
    int priorityId;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
} Process;

// Function prototypes
void initializeProcesses(Process processes[], int num);
void calculate_fcfs(Process processes[], int num);
void calclulate_sjf(Process processes[], int num);
void calclulate_srtf(Process processes[], int num);
void calculate_rr(Process processes[], int num, int quantam);
void calculate_priority(Process processes[], int num, int quantam);

#endif /* MY_FUNCTIONS_H */