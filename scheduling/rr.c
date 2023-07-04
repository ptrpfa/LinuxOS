#include <stdio.h>
#include <limits.h>
#include "schedule.h"

void rr_swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

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
    int rt[num];
    int responseFlag[num];
    int currentTime = 0, finishTime = 0, complete = 0;

    int ganttBar[100];
    int ganttCount = 0;

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0;
    }

    for (int i = 0; i < num; i++) {
        rt[i] = processes[i].burstTime;
        responseFlag[i] = 0;
    }

    while(complete != num) {
        int flag = 0;
        for (int j = 0; j < num; j++) {
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0) {
                flag = 1;
                if(responseFlag[j] == 0) {
                    processes[j].responseTime = currentTime;
                    responseFlag[j] = 1;
                }
                if (rt[j] > quantum) {
                    rt[j] -= quantum;
                    for (int i = 0; i < quantum; i++)
                    {
                        ganttBar[ganttCount] = processes[j].processId;
                        ganttCount++;
                    }
                    
                    currentTime += quantum;
                }
                else {
                    currentTime += rt[j];
                    for (int i = 0; i < rt[j]; i++)
                    {
                        ganttBar[ganttCount] = processes[j].processId;
                        ganttCount++;
                    }
                    
                    rt[j] = 0;
                    finishTime = currentTime;
                    processes[j].turnaroundTime = finishTime - processes[j].arrivalTime;
                    processes[j].waitingTime = processes[j].turnaroundTime - processes[j].burstTime;
                    complete++;
                }
            }
        }
        if(flag == 0) {
            ganttCount++;
            currentTime++;
        }
    }
    
    draw_gantt(ganttBar, ganttCount);
    printf("\n");

}

void calculate_rr(Process processes[], int num, int quantam){

    rr_sortProcesses(processes, num);
    calculate_for_rr(processes, num, quantam);

}