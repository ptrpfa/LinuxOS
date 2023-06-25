#include <stdio.h>
#include "schedule.h"

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcesses(Process processes[], int num_process) {
    for (int i = 0; i < num_process - 1; i++) {
        for (int j = 0; j < num_process - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void calculate(Process processes[], int num){

    int currentTime = 0;

    for (int i = 0; i < num; i++)
    {
        while (currentTime < processes[i].arrivalTime){
            currentTime++;
        }
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
    
}

void calculate_fcfs(Process processes[], int num){
    
    sortProcesses(processes, num);
    calculate(processes, num);

}

// void calculate_fcfs(Process processes[], int num){

//     int rt[num];
//     int arrived[num];
//     int completed[num];
//     int flag = 0, current = -1, currentTime = 0, finishTime = 0, complete = 0, occupied = 0, responseTime = 0;

//     for (int i = 0;i<num;i++){
//         rt[i] = processes[i].burstTime;
//         arrived[i] = 0;
//         completed[i] = 0;
//     }

//     while(complete!=num){

//         for (int j = 0;j<num;j++){
//             if (processes[j].arrivalTime <= currentTime && rt[j] != 0){
//                 arrived[j] = 1;
//             }
//         }

//         for (int j = 0;j<num;j++){
//             if (arrived[j] == 1 && completed[j] != 1 && occupied == 0){
//                     flag = 1;
//                     current = j;
//                     occupied = 1;
//                     responseTime = currentTime;
//                 };
//         }

//         if (flag == 1){
//             rt[current]--;
//             currentTime++;
//             if (rt[current] == 0){
//                 complete++;
//                 arrived[current] = 0;
//                 completed[current] = 1;
//                 finishTime = currentTime;
//                 processes[current].turnaroundTime = finishTime - processes[current].arrivalTime;
//                 processes[current].waitingTime = processes[current].turnaroundTime - processes[current].burstTime;
//                 processes[current].responseTime = responseTime - processes[current].arrivalTime;
//                 occupied = 0;
//                 current = -1;
//                 flag = 0;
//             }
//         }
//         else{
//             currentTime++;
//         }
//     }
// }