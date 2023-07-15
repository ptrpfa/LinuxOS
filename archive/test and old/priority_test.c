#include <stdio.h>
#include <limits.h>

typedef struct{
    int processId;
    int priorityId;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    int finishTime;
} Process;

void calculate_priority(Process processes[], int num){

    int rt[num];
    int priority[num];
    int arrived[num];
    int completed[num];
    int responded[num];
    int flag = 0, priorityIndex = -1, currentTime = 0, lowest_priority = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

    for (int i = 0;i<num;i++){
        rt[i] = processes[i].burstTime;
        priority[i] = processes[i].priorityId;
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
                if (priorityIndex == -1 || priority[j] < lowest_priority || (priority[j] == lowest_priority && processes[j].arrivalTime < processes[priorityIndex].arrivalTime)){
                    flag = 1;
                    lowest_priority = priority[j];
                    priorityIndex = j;
                }
            }
        }

        if (flag == 1){
            if (responded[priorityIndex] == 0){
            responseTime = currentTime - processes[priorityIndex].arrivalTime;
            processes[priorityIndex].responseTime = responseTime;
            responded[priorityIndex] = 1;
            }
            rt[priorityIndex]--;
            currentTime++;
            if (rt[priorityIndex] == 0){
                complete++;
                arrived[priorityIndex] = 0;
                completed[priorityIndex] = 1;
                finishTime = currentTime;
                lowest_priority = INT_MAX;
                processes[priorityIndex].turnaroundTime = finishTime - processes[priorityIndex].arrivalTime;
                processes[priorityIndex].waitingTime = processes[priorityIndex].turnaroundTime - processes[priorityIndex].burstTime;
                priorityIndex = -1;
                flag = 0;
            }
        }
        else{
            currentTime++;
        }
    }
}

int main(){

    Process processes[6] = {
        {1,4,0,1},
        {2,3,2,3},
        {3,1,0,7},
        {4,3,3,5},
        {5,4,5,1},
        {6,1,5,8},
    };

    calculate_priority(processes, 6);

    for (int i=0;i<6;i++){
        printf("PID: %d\n", processes[i].processId);
        printf("Arrival Time: %d\n", processes[i].arrivalTime);
        printf("Burst Time: %d\n", processes[i].burstTime);
        printf("Turnaround time: %d\n", processes[i].turnaroundTime);       
        printf("Waiting time: %d\n", processes[i].waitingTime);
        printf("Reponse time: %d\n", processes[i].responseTime);        
        printf("Finish time: %d\n", processes[i].finishTime);
        printf("\n");
    }

    return 0;

}