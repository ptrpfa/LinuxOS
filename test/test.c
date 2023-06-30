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

void calclulate_srtf(Process processes[], int num){

    int rt[num];
    int arrived[num];
    int completed[num];
    int responded[num];
    int flag = 0, shortest = -1, currentTime = 0, minimum = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

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
            if (arrived[j] == 1 && completed[j] != 1){
                if (shortest == -1 || rt[j] < minimum || (rt[j] == minimum && processes[j].arrivalTime < processes[shortest].arrivalTime)){
                    flag = 1;
                    minimum = rt[j];
                    shortest = j;
                }
            }
        }

        if (flag == 1){
            if (responded[shortest] == 0){
            responseTime = currentTime - processes[shortest].arrivalTime;
            processes[shortest].responseTime = responseTime;
            responded[shortest] = 1;
            }
            rt[shortest]--;
            currentTime++;
            if (rt[shortest] == 0){
                complete++;
                arrived[shortest] = 0;
                completed[shortest] = 1;
                finishTime = currentTime;
                processes[shortest].finishTime = finishTime;
                minimum = INT_MAX;
                processes[shortest].turnaroundTime = finishTime - processes[shortest].arrivalTime;
                processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
                shortest = -1;
                flag = 0;
            }
        }
        else{
            currentTime++;
        }
    }
}


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
                processes[shortest].finishTime = finishTime;
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


int main(){

    Process processes[6] = {
        {1,0,2,5},
        {2,0,2,6},
        {3,0,4,7},
        {4,0,0,8},
        {5,0,6,4},
        {6,0,6,2},
    };

    calclulate_srtf(processes, 6);

    for (int i=0;i<6;i++){
        printf("PID: %d\n", processes[i].processId);
        printf("Arrival Time: %d\n", processes[i].arrivalTime);
        printf("Burst Time: %d\n", processes[i].burstTime);
        printf("Turnaround time: %d\n", processes[i].turnaroundTime);    
        printf("Waiting time: %d\n", processes[i].waitingTime);
        printf("Reponse time: %d\n", processes[i].responseTime);   
        printf("Finish Time: %d\n", processes[i].finishTime);
        printf("\n");
    }

    return 0;

}