#include <stdio.h>
#include <limits.h>
#include "schedule.h"

void calculate_priority(Process processes[], int num){

    int rt[num];
    int priority[num];
    int arrived[num];
    int completed[num];
    int responded[num];
    int flag = 0, priorityIndex = -1, currentTime = 0, lowest_priority = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

    int ganttBar[100];
    int ganttCount = 0;

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0;
    }

    for (int i = 0;i<num;i++){
        rt[i] = processes[i].burstTime;
        priority[i] = processes[i].priorityId;
        arrived[i] = 0;
        completed[i] = 0;
        responded[i] = 0;
    }

    while(complete!=num){

        for (int j = 0;j<num;j++){
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0){
                arrived[j] = 1;
            }
        }

        for (int j = 0;j<num;j++){
            if (arrived[j] == 1 && completed[j] != 1){
                if (priorityIndex == -1 || priority[j] < lowest_priority || (priority[j] == lowest_priority && processes[j].arrivalTime < processes[priorityIndex].arrivalTime)){
                    flag = 1;
                    lowest_priority = priority[j];
                    priorityIndex = j;
                }
            }
        }

        if (flag == 1){
            if (responded[priorityIndex] == 0){
            responseTime = currentTime - processes[priorityIndex].arrivalTime;
            processes[priorityIndex].responseTime = responseTime;
            responded[priorityIndex] = 1;
            }
            rt[priorityIndex]--;
            ganttBar[ganttCount] = priorityIndex + 1;
            ganttCount++;
            currentTime++;
            if (rt[priorityIndex] == 0){
                complete++;
                arrived[priorityIndex] = 0;
                completed[priorityIndex] = 1;
                finishTime = currentTime;
                lowest_priority = INT_MAX;
                processes[priorityIndex].turnaroundTime = finishTime - processes[priorityIndex].arrivalTime;
                processes[priorityIndex].waitingTime = processes[priorityIndex].turnaroundTime - processes[priorityIndex].burstTime;
                priorityIndex = -1;
                flag = 0;
            }
        }
        else{
            ganttCount++;
            currentTime++;
        }
    }

    draw_gantt(ganttBar, ganttCount);
    printf("\n");
}