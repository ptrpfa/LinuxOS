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

void calclulate(Process processes[], int num){

    int rt[num];
    int arrived[num];
    int completed[num];
    int responded[num];
    int shortest = 0, currentTime = 0, minimum = INT_MAX, finishTime = 0, complete = 0, prev = 0, responseTime = 0;

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
            if (arrived[j] == 1 && rt[j]<minimum && completed[j] != 1){
                    minimum = rt[j];
                    prev = shortest;
                    shortest = j;
                    if (shortest != prev && responded[shortest] == 0)
                    {
                        responded[shortest] = 1;
                        responseTime = currentTime;
                        processes[shortest].responseTime = responseTime - processes[shortest].arrivalTime;
                    }
                };
        }

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
            shortest = 0;
        }
    }
}

int main(){

    Process processes[4] = {
        {1,0,0,8},
        {2,0,1,4},
        {3,0,2,9},
        {4,0,3,5}
    };

    calclulate(processes, 4);

    for (int i=0;i<4;i++){
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