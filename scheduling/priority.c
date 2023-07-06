#include <stdio.h>
#include <limits.h>
#include "schedule.h"

void calculate_priority(Process processes[], int num){

    int rt[num]; // initialize array to keep track of the remaining time left to execute a process
    int priority[num]; // initialize array to keep track of priority of processes
    int arrived[num]; // initialize array to keep track of which process has arrived
    int completed[num]; // initialize array to keep track of which process has been completed
    int responded[num]; // initialize array to keep track of which process has been responded to
    int flag = 0, priorityIndex = -1, currentTime = 0, highest_priority = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

    int ganttBar[100]; // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0;i<num;i++){
        rt[i] = processes[i].burstTime; // assign the burst time of each process and represent them as the remaining time a process needs to run
        priority[i] = processes[i].priorityId; // assign the priority of each process to the array
        arrived[i] = 0; // set all index to 0 as no process has arrived yet
        completed[i] = 0; // set all index to 0 as no process has been completed
        responded[i] = 0; // set all index to 0 as no process has been responded to yet
    }

    while(complete!=num){ // while there are still processes to be completed, keep on running

        for (int j = 0;j<num;j++){
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0){
                arrived[j] = 1; // if the process has arrived and the remaining time of it is not 0, set the process to 1
            }
        }

        for (int j = 0;j<num;j++){
            if (arrived[j] == 1 && completed[j] != 1){ // if it has arrived and is not completed, then proceed
                if (priorityIndex == -1 || priority[j] < highest_priority || (priority[j] == highest_priority && processes[j].arrivalTime < processes[priorityIndex].arrivalTime)){ // check for the highest priority of the processes that have arrived and are not completed, if there are 2 processes with the same priority, take the process that arrived earlier
                    flag = 1; // set the flag at a process is set to be executed
                    highest_priority = priority[j]; // assign a highest priority so that the loop will be able to find the next highest priority
                    priorityIndex = j; // assign the priority index to the current process index
                }
            }
        }

        if (flag == 1){ // if flag is 1, a process is to be executed
            if (responded[priorityIndex] == 0){ // if the current process has not be responded to yet, calculate the response time and assign it to the process struct
            responseTime = currentTime - processes[priorityIndex].arrivalTime;
            processes[priorityIndex].responseTime = responseTime;
            responded[priorityIndex] = 1; // set the process to responded
            }
            rt[priorityIndex]--; // reduce the remaining time of the current process by 1
            ganttBar[ganttCount] = processes[priorityIndex].processId; // assign the current index of the gantt bar to the process ID of the currently executing process
            ganttCount++;
            currentTime++;
            if (rt[priorityIndex] == 0){ // if remaining time is 0, process has finished executing
                complete++; // increment complete variable by 1
                arrived[priorityIndex] = 0; // set the finish process to 0 in the arrived array
                completed[priorityIndex] = 1; // set the finish process to 1 in the complete array
                finishTime = currentTime;
                highest_priority = INT_MAX; // set the highest priority to max to allow the next priority to be found later
                processes[priorityIndex].turnaroundTime = finishTime - processes[priorityIndex].arrivalTime; // assign turnaround time
                processes[priorityIndex].waitingTime = processes[priorityIndex].turnaroundTime - processes[priorityIndex].burstTime; // assign waiting time
                priorityIndex = -1; // reset priority index variable
                flag = 0; // set flag to 0 as we do not know if there will be another process to be executed in the next second
            }
        }
        else{ // if flag is 0, increase time as no process is ready to be executed
            ganttCount++;
            currentTime++;
        }
    }

    draw_gantt(ganttBar, ganttCount); // draw the gantt chart with function
    printf("\n");
}