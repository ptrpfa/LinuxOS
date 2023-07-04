#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "schedule.h"

void initializeProcesses(Process processes[], int num){

    srand(time(NULL));

    int priorityCount[6] = {0};
    int arrivalCount[9] = {0};
    int burstCount[8] = {0};

    for (int i = 0; i < num; i++) {
        processes[i].processId = i + 1;

        int priorityId;
        do{
            priorityId = rand() % 4 + 1;
        } while (priorityCount[priorityId - 1] >= 2);

        processes[i].priorityId = priorityId;
        priorityCount[priorityId - 1]++;

        int arrivalTime;
        do {
            arrivalTime = rand() % 9;
        } while (arrivalCount[arrivalTime] >= 2); 

        processes[i].arrivalTime = arrivalTime;
        arrivalCount[arrivalTime]++;

        int burstTime;
        do{
            burstTime = rand() % 8 + 1;
        } while (burstCount[burstTime - 1] >= 3);

        processes[i].burstTime = burstTime;
        burstCount[burstTime - 3]++;

    }
}