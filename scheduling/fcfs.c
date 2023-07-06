#include <stdio.h>
#include "schedule.h"

// fcfs helper function for sorting to swap process positions in the array of structs
void fcfs_swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// sort the array of structs based on arrival time through bubble sort algorithm
void fcfs_sortProcesses(Process processes[], int num_process) {
    for (int i = 0; i < num_process - 1; i++) {
        for (int j = 0; j < num_process - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                fcfs_swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void calculate_for_fcfs(Process processes[], int num){

    int currentTime = 0; // initialize current time to 0

    int ganttBar[100]; // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0; i < num; i++)
    {
        while (currentTime < processes[i].arrivalTime){ // check that while the current time is < than the process arrival time, increment the current time as the process has not arrived
            ganttCount++;
            currentTime++;
        }
        processes[i].responseTime = currentTime - processes[i].arrivalTime; // assignment of response time
        currentTime += processes[i].burstTime; // add burst time to current time to finish process execution
        for (int j = 0; j < processes[i].burstTime; j++)
        {
           ganttBar[ganttCount] = processes[i].processId; // assign the number of seconds of burst time to the array index to keep track of the order execution of processes
           ganttCount++;
        }
        
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime; // assignment of turnaround time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime; // assignment of waiting time
    }

    draw_gantt(ganttBar, ganttCount); // draw the gantt chart with a function
    printf("\n");
    
}

// main function to sort and calculate the process details
void calculate_fcfs(Process processes[], int num){
    
    fcfs_sortProcesses(processes, num);
    calculate_for_fcfs(processes, num);

}