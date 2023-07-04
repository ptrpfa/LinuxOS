#include <stdio.h>
#include "schedule.h"

void fcfs_swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

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

    int currentTime = 0;

    int ganttBar[100];
    int ganttCount = 0;

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0;
    }

    for (int i = 0; i < num; i++)
    {
        while (currentTime < processes[i].arrivalTime){
            ganttCount++;
            currentTime++;
        }
        processes[i].responseTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        for (int j = 0; j < processes[i].burstTime; j++)
        {
           ganttBar[ganttCount] = processes[i].processId;
           ganttCount++;
        }
        
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

    draw_gantt(ganttBar, ganttCount);
    printf("\n");
    
}

void calculate_fcfs(Process processes[], int num){
    
    fcfs_sortProcesses(processes, num);
    calculate_for_fcfs(processes, num);

}