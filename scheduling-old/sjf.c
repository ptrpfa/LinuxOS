#include <stdio.h>
#include <limits.h>
#include "schedule.h"

void calclulate_sjf(Process processes[], int num){

    int rt[num]; // initialize array to keep track of the remaining time left to execute a process
    int arrived[num]; // initialize array to keep track of which process has arrived
    int completed[num]; // initialize array to keep track of which process has been completed
    int flag = 0, shortest = -1, currentTime = 0, minimum = INT_MAX, finishTime = 0, complete = 0, occupied = 0, responseTime = 0;

    int ganttBar[100]; // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }
    

    for (int i = 0;i<num;i++){
        rt[i] = processes[i].burstTime; // assign the burst time of each process and represent them as the remaining time a process needs to run
        arrived[i] = 0; // set all index to 0 as no process has arrived yet
        completed[i] = 0; // set all index to 0 as no process has been completed
    }

    while(complete!=num){

        for (int j = 0;j<num;j++){
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0){
                arrived[j] = 1; // if the process has arrived and the remaining time of it is not 0, set the process to 1
            }
        }

        for (int j = 0;j<num;j++){
            if (arrived[j] == 1 && completed[j] != 1 && occupied == 0){ // if it has arrived and is not completed, and there are currently no processes executing, then proceed
                if (shortest == -1 || rt[j] < minimum || (rt[j] == minimum && processes[j].arrivalTime < processes[shortest].arrivalTime)){ // check for the shortest remaining time of the processes that have arrived and are not completed, if there are 2 processes with the same remaining time that are the shortest, take the process that arrived earlier
                    flag = 1; // set the flag at a process is set to be executed
                    minimum = rt[j]; // assign a minimum so that the loop will be able to find the next minimum
                    shortest = j; // assign shortest to the current process index
                    responseTime = currentTime; // assign response time to be the current time for calculation of the response time of the process to be completed later
                }
            }
        }

        if (flag == 1){ // if flag is 1, a process is to be executed
            occupied = 1; // set occupied to 1 so that no other process can take over even if it has a shorter remaining time as it is non preemptive
            rt[shortest]--; // reduce the remaining time of the current process by 1
            ganttBar[ganttCount] = processes[shortest].processId; // assign the current index of the gantt bar to the process ID of the currently executing process
            ganttCount++;
            currentTime++;
            if (rt[shortest] == 0){ // if remaining time is 0, process has finished executing
                complete++; // increment complete variable by 1
                arrived[shortest] = 0; // set the finish process to 0 in the arrived array
                completed[shortest] = 1; // set the finish process to 1 in the complete array
                finishTime = currentTime;
                minimum = INT_MAX; // set the minimum to max to allow the next minimum to be found later
                processes[shortest].turnaroundTime = finishTime - processes[shortest].arrivalTime; // assign turnaround time
                processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime; // assign waiting time
                processes[shortest].responseTime = responseTime - processes[shortest].arrivalTime; // assign response time
                occupied = 0; // set occupied to 0 to allow other process to be executed
                shortest = -1; // reset shortest variable
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