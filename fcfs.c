#include <stdio.h>

typedef struct{
    int processId;
    int priorityId;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
} Process;

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
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

}

int main(){

    Process processes[3] = {
        {1,0,2,24},
        {2,0,0,3},
        {3,0,1,3}
    };

    sortProcesses(processes,3);
    findtt(processes,3);
    findwt(processes,3);

    for (int i=0;i<3;i++){
        printf("PID: %d\n", processes[i].processId);
        printf("Arrival Time: %d\n", processes[i].arrivalTime);
        printf("Burst Time: %d\n", processes[i].burstTime);
        printf("Waiting time: %d\n", processes[i].waitingTime);
        printf("Turnaround time: %d\n", processes[i].turnaroundTime);        
        printf("\n");
    }

    return 0;

}