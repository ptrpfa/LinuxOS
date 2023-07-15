#include <stdio.h>
#include <limits.h>
#include "schedule.h"


// rr helper function for sorting to swap process positions in the array of structs
void rr_swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// sort the array of structs based on arrival time through bubble sort algorithm
void rr_sortProcesses(Process processes[], int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                rr_swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void calculate_for_rr(Process processes[], int num, int quantum) {
    int rt[num]; // initialize array to keep track of the remaining time left to execute a process
    int responseFlag[num]; // initialize array to keep track of which process has been responded to
    int currentTime = 0, finishTime = 0, complete = 0;

    int ganttBar[100]; // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0; i < num; i++) {
        rt[i] = processes[i].burstTime; // assign the burst time of each process and represent them as the remaining time a process needs to run
        responseFlag[i] = 0; // set all index to 0 as no process has been responded to yet
    }

    while(complete != num) {
        int flag = 0; // set flag to 0 as no process is set to run yet
        for (int j = 0; j < num; j++) {
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0) { // if it has arrived and is not completed, then proceed
                flag = 1; // process has arrived, set flag to run as a new process is expected to run
                if(responseFlag[j] == 0) { // if the current process has not be responded to yet, calculate the response time and assign it to the process struct
                    processes[j].responseTime = currentTime - processes[j].arrivalTime;
                    responseFlag[j] = 1; // set the process to responded
                }
                if (rt[j] > quantum) { // check if remaining time of process is more than quantam
                    rt[j] -= quantum;
                    for (int i = 0; i < quantum; i++)
                    {
                        ganttBar[ganttCount] = processes[j].processId;  // assign the number of seconds of quantam to the array index to keep track of the order execution of processes
                        ganttCount++;
                    }
                    
                    currentTime += quantum; // increment current time by quantam
                }
                else {
                    currentTime += rt[j]; // if rt <= quantam, increment current time by remaining time of the process left to execute
                    for (int i = 0; i < rt[j]; i++)
                    {
                        ganttBar[ganttCount] = processes[j].processId; // assign the number of seconds of remaining time to the array index to keep track of the order execution of processes
                        ganttCount++;
                    }
                    
                    rt[j] = 0; // set remaining time to 0
                    finishTime = currentTime;
                    processes[j].turnaroundTime = finishTime - processes[j].arrivalTime; // assign turnaround time
                    processes[j].waitingTime = processes[j].turnaroundTime - processes[j].burstTime; // assign waiting time
                    complete++;
                }
            }
        }
        if(flag == 0) { // if flag is 0, increase time as no process is ready to be executed
            ganttCount++;
            currentTime++;
        }
    }
    
    draw_gantt(ganttBar, ganttCount); // draw the gantt chart with function
    printf("\n");

}

// main function to sort and calculate the process details
void calculate_rr(Process processes[], int num, int quantam){

    rr_sortProcesses(processes, num);
    calculate_for_rr(processes, num, quantam);

}