#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process{
    int processId;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void initializeProcesses(struct Process processes[], int num_process){

    srand(time(NULL));

    int arrivalCount[9] = {0};
    int burstCount[8] = {0};

    for (int i = 0; i < num_process; i++) {
        processes[i].processId = i + 1;

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

int main(){

    struct Process processes[6];

    initializeProcesses(processes, 6);

    for (int i=0;i<6;i++){
        printf("PID: %d\n", processes[i].processId);
        printf("Arrival Time: %d\n", processes[i].arrivalTime);
        printf("Burst Time: %d\n", processes[i].burstTime);
        printf("\n");
    }

    return 0;


}