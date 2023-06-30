#include <stdio.h>
#include <limits.h>
#include "schedule.h"

// typedef struct{
//     int processId;
//     int priorityId;
//     int arrivalTime;
//     int burstTime;
//     int turnaroundTime;
//     int waitingTime;
//     int responseTime;
// } Process;

void calclulate_sjf(Process processes[], int num){

    int rt[num];
    int arrived[num];
    int completed[num];
    int flag = 0, shortest = -1, currentTime = 0, minimum = INT_MAX, finishTime = 0, complete = 0, occupied = 0, responseTime = 0;

    for (int i = 0;i<num;i++){
        rt[i] = processes[i].burstTime;
        arrived[i] = 0;
        completed[i] = 0;
    }

    while(complete!=num){

        for (int j = 0;j<num;j++){
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0){
                arrived[j] = 1;
            }
        }

        for (int j = 0;j<num;j++){
            if (arrived[j] == 1 && completed[j] != 1 && occupied == 0){
                if (shortest == -1 || rt[j] < minimum || (rt[j] == minimum && processes[j].arrivalTime < processes[shortest].arrivalTime)){
                    flag = 1;
                    minimum = rt[j];
                    shortest = j;
                    responseTime = currentTime;
                }
            }
        }

        if (flag == 1){
            occupied = 1;
            rt[shortest]--;
            currentTime++;
            if (rt[shortest] == 0){
                complete++;
                arrived[shortest] = 0;
                completed[shortest] = 1;
                finishTime = currentTime;
                minimum = INT_MAX;
                processes[shortest].turnaroundTime = finishTime - processes[shortest].arrivalTime;
                processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
                processes[shortest].responseTime = responseTime - processes[shortest].arrivalTime;
                occupied = 0;
                shortest = -1;
                flag = 0;
            }
        }
        else{
            currentTime++;
        }
    }
}


// int main(){

//     Process processes[4] = {
//         {1,0,2,4},
//         {2,0,3,3},
//         {3,0,3,5},
//         {4,0,2,2},
//     };

//     calclulate(processes, 4);

//     for (int i=0;i<4;i++){
//         printf("PID: %d\n", processes[i].processId);
//         printf("Arrival Time: %d\n", processes[i].arrivalTime);
//         printf("Burst Time: %d\n", processes[i].burstTime);
//         printf("Turnaround time: %d\n", processes[i].turnaroundTime);    
//         printf("Waiting time: %d\n", processes[i].waitingTime);
//         printf("Reponse time: %d\n", processes[i].responseTime);   
//         printf("\n");
//     }

//     return 0;

// }