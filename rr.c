#include <stdio.h>
#include<limits.h>

typedef struct{
    int processId;
    int priorityId;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
} Process;

void calculate(Process processes[], int num, int quantum) {
    int rt[num];
    int responseFlag[num];
    int currentTime = 0, finishTime = 0, complete = 0;

    for (int i = 0; i < num; i++) {
        rt[i] = processes[i].burstTime;
        responseFlag[i] = 0;
    }

    while(complete != num) {
        int flag = 0;
        for (int j = 0; j < num; j++) {
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0) {
                flag = 1;
                if(responseFlag[j] == 0) {
                    processes[j].responseTime = currentTime;
                    responseFlag[j] = 1;
                }
                if (rt[j] > quantum) {
                    rt[j] -= quantum;
                    currentTime += quantum;
                }
                else {
                    currentTime += rt[j];
                    rt[j] = 0;
                    finishTime = currentTime;
                    processes[j].turnaroundTime = finishTime - processes[j].arrivalTime;
                    processes[j].waitingTime = finishTime - processes[j].burstTime;
                    complete++;
                }
            }
        }
        if(flag == 0) {
            currentTime++;
        }
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


int main(){

    Process processes[3] = {
        {1,0,0,24},
        {2,0,0,3},
        {3,0,0,3},
    };

    sortProcesses(processes, 3);
    calculate(processes, 3, 4);

    for (int i=0;i<3;i++){
        printf("PID: %d\n", processes[i].processId);
        printf("Arrival Time: %d\n", processes[i].arrivalTime);
        printf("Burst Time: %d\n", processes[i].burstTime);
        printf("Turnaround time: %d\n", processes[i].turnaroundTime);       
        printf("Waiting time: %d\n", processes[i].waitingTime);
        printf("Reponse time: %d\n", processes[i].responseTime);        
        printf("\n");
    }

    return 0;

}