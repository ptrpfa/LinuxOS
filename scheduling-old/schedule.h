#ifndef MY_FUNCTIONS_H   // Include guard
#define MY_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 100

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

typedef struct{
    float turnaround_average;
    float waiting_average;
    float response_average;
} Algo;

// Function prototypes
void draw_gantt(int gantt[], int size);
void initializeProcesses(Process processes[], int num);
void calculate_fcfs(Process processes[], int num);
void calclulate_sjf(Process processes[], int num);
void calclulate_srtf(Process processes[], int num);
void calculate_rr(Process processes[], int num, int quantam);
void calculate_priority(Process processes[], int num);
void checkFastestAlgorithms(Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo);
void checkFastestAlgorithms_file(FILE *file, Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo);
void printing(Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int num);

#endif /* MY_FUNCTIONS_H */