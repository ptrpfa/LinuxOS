#include <stdio.h>
#include <limits.h>
#include "schedule.h"

void calclulate_srtf(Process processes[], int num){

    int rt[num];
    int arrived[num];
    int completed[num];
    int responded[num];
    int flag = 0, shortest = -1, currentTime = 0, minimum = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

    int ganttBar[100];
    int ganttCount = 0;

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0;
    }

    for (int i = 0;i<num;i++){
        rt[i] = processes[i].burstTime;
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
                if (shortest == -1 || rt[j] < minimum || (rt[j] == minimum && processes[j].arrivalTime < processes[shortest].arrivalTime)){
                    flag = 1;
                    minimum = rt[j];
                    shortest = j;
                }
            }
        }

        if (flag == 1){
            if (responded[shortest] == 0){
            responseTime = currentTime - processes[shortest].arrivalTime;
            processes[shortest].responseTime = responseTime;
            responded[shortest] = 1;
            }
            rt[shortest]--;
            ganttBar[ganttCount] = shortest + 1;
            ganttCount++;
            currentTime++;
            if (rt[shortest] == 0){
                complete++;
                arrived[shortest] = 0;
                completed[shortest] = 1;
                finishTime = currentTime;
                minimum = INT_MAX;
                processes[shortest].turnaroundTime = finishTime - processes[shortest].arrivalTime;
                processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
                shortest = -1;
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