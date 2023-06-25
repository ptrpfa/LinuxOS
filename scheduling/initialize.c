#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void initializeProcesses(Process processes[], int num){

    srand(time(NULL));

    int priorityCount[6] = {0};
    int arrivalCount[9] = {0};
    int burstCount[8] = {0};

    for (int i = 0; i < num; i++) {
        processes[i].processId = i + 1;

        int priorityId;
        do{
            priorityId = rand() % 6 + 1;
        } while (priorityCount[priorityId - 1] >= 1);

        processes[i].priorityId = priorityId;
        priorityCount[priorityId - 1]++;

        int arrivalTime;
        do {
            arrivalTime = rand() % 9;
        } while (arrivalCount[arrivalTime] >= 3); 

        processes[i].arrivalTime = arrivalTime;
        arrivalCount[arrivalTime]++;

        int burstTime;
        do{
            burstTime = rand() % 8 + 3;
        } while (burstCount[burstTime - 3] >= 3);

        processes[i].burstTime = burstTime;
        burstCount[burstTime - 3]++;

    }
}

// int main(){

//     Process processes[6];

//     initializeProcesses(processes, 6);

//     for (int i=0;i<6;i++){
//         printf("PID: %d\n", processes[i].processId);
//         printf("Priority ID: %d\n", processes[i].priorityId);
//         printf("Arrival Time: %d\n", processes[i].arrivalTime);
//         printf("Burst Time: %d\n", processes[i].burstTime);
//         printf("\n");
//     }

//     return 0;

// }