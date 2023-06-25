#include <stdio.h>
#include <limits.h>
#include "Schedule.h"

void setup(Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], int num){

    Process processes[6];

    initializeProcesses(processes, num);

    for (int i = 0; i < num; i++)
    {
        printf("PID: %d\n", processes[i].processId);
        printf("Arrival Time: %d\n", processes[i].arrivalTime);
        printf("Burst Time: %d\n", processes[i].burstTime);
        printf("Priority ID: %d\n", processes[i].priorityId);
    }
    

    for (int i = 0; i < num; i++)
    {
        fcfs_processes[i].processId = processes[i].processId;
        fcfs_processes[i].arrivalTime = processes[i].arrivalTime;
        fcfs_processes[i].burstTime = processes[i].burstTime;
        fcfs_processes[i].priorityId = processes[i].priorityId;

        sjf_processes[i].processId = processes[i].processId;
        sjf_processes[i].arrivalTime = processes[i].arrivalTime;
        sjf_processes[i].burstTime = processes[i].burstTime;
        sjf_processes[i].priorityId = processes[i].priorityId;

        srtf_processes[i].processId = processes[i].processId;
        srtf_processes[i].arrivalTime = processes[i].arrivalTime;
        srtf_processes[i].burstTime = processes[i].burstTime;
        srtf_processes[i].priorityId = processes[i].priorityId;

        rr_processes[i].processId = processes[i].processId;
        rr_processes[i].arrivalTime = processes[i].arrivalTime;
        rr_processes[i].burstTime = processes[i].burstTime;
        rr_processes[i].priorityId = processes[i].priorityId;

        priority_processes[i].processId = processes[i].processId;
        priority_processes[i].arrivalTime = processes[i].arrivalTime;
        priority_processes[i].burstTime = processes[i].burstTime;
        priority_processes[i].priorityId = processes[i].priorityId;
    }
    

}

int main(){

    int choice;
    int num = 6;
    Process fcfs_processes[6];
    Process sjf_processes[6];
    Process srtf_processes[6];
    Process rr_processes[6];
    Process priority_processes[6];

    printf("Welcome to CSC1107OS scheduling algorithm program!\n");
    printf("--------------------------------------------------\n");
    while(1){
        printf("Please select an option\n");
        printf("1) FCFS\n");
        printf("2) SJF\n");
        printf("3) SRTF\n");
        printf("4) RR\n");
        printf("5) Priority\n");
        printf("6) Quit\n");
        printf("Enter an option: ");

        scanf("%d", &choice);

        while(choice < 1 || choice > 6){
            printf("Invalid input! Please enter a number between 1 and 6: ");
            scanf("%d", &choice);
            printf("\n");
        }

        setup(fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, num);

        switch(choice) {
            case 1:
                printf("You chose FCFS\n");
                break;
            case 2:
                printf("You chose SJF\n");
                // Add code for SJF scheduling algorithm here
                break;
            case 3:
                printf("You chose SRTF\n");
                // Add code for SRTF scheduling algorithm here
                break;
            case 4:
                printf("You chose RR\n");
                // Add code for RR scheduling algorithm here
                break;
            case 5:
                printf("You chose Priority\n");
                // Add code for Priority scheduling algorithm here
                break;
            case 6:
                printf("Quitting program...\n");
                return 0; // Exit the program
        }
    }
    return 0;
}


// FOR TESTING
// for (int i = 0; i < num; i++)
// {
//     printf("PID: %d\n", fcfs_processes[i].processId);
//     printf("Arrival Time: %d\n", fcfs_processes[i].arrivalTime);
//     printf("Burst Time: %d\n", fcfs_processes[i].burstTime);
//     printf("Priority ID: %d\n", fcfs_processes[i].priorityId);

//     printf("PID: %d\n", sjf_processes[i].processId);
//     printf("Arrival Time: %d\n", sjf_processes[i].arrivalTime);
//     printf("Burst Time: %d\n", sjf_processes[i].burstTime);
//     printf("Priority ID: %d\n", sjf_processes[i].priorityId);

//     printf("PID: %d\n", srtf_processes[i].processId);
//     printf("Arrival Time: %d\n", srtf_processes[i].arrivalTime);
//     printf("Burst Time: %d\n", srtf_processes[i].burstTime);
//     printf("Priority ID: %d\n", srtf_processes[i].priorityId);

//     printf("PID: %d\n", rr_processes[i].processId);
//     printf("Arrival Time: %d\n", rr_processes[i].arrivalTime);
//     printf("Burst Time: %d\n", rr_processes[i].burstTime);
//     printf("Priority ID: %d\n", rr_processes[i].priorityId);

//     printf("PID: %d\n", priority_processes[i].processId);
//     printf("Arrival Time: %d\n", priority_processes[i].arrivalTime);
//     printf("Burst Time: %d\n", priority_processes[i].burstTime);
//     printf("Priority ID: %d\n", priority_processes[i].priorityId);
// }