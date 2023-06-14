#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int processId;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void initializeProcesses(Process processes[], int num_process){

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

void findtt(Process processes[], int num_process){

    int currentTime = 0;

    for (int i = 0; i < num_process; i++)
    {
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
    }
    
}

void findwt(Process processes[], int num_process){
    
    for (int i = 0; i < num_process; i++)
    {
        processes[i].burstTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

}

int main(){

    Process processes[6];

    initializeProcesses(processes, 6);
    sortProcesses(processes, 6);
    findtt(processes, 6);

    for (int i=0;i<6;i++){
        printf("PID: %d\n", processes[i].processId);
        printf("Arrival Time: %d\n", processes[i].arrivalTime);
        printf("Burst Time: %d\n", processes[i].burstTime);
        printf("TT time: %d\n", processes[i].turnaroundTime);
        printf("\n");
    }

    return 0;


}