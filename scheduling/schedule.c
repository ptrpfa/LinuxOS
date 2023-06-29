#include <stdio.h>
#include <limits.h>
#include "Schedule.h"

void printTable(Process processes[6]){

    char headers[4][20] = {
        "Process ID",
        "Arrival Time",
        "Burst Time",
        "Priority"
    };

    int table[6][4];

    for (int i = 0; i < 6; i++)
    {
        int j = 0;

        table[i][j] = processes[i].processId;
        table[i][j+1] = processes[i].arrivalTime;
        table[i][j+2] = processes[i].burstTime;
        table[i][j+3] = processes[i].priorityId;
        
    }
    

    // Print the top border
    printf("%c", 218); // Top-left corner
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", 196); // Horizontal line
        }
        if (i != 3) {
            printf("%c", 194); // Intersection
        }
    }
    printf("%c\n", 191); // Top-right corner

    // Print the headers
    printf("%c", 179); // Vertical line
    for (int i = 0; i < 4; i++) {
        printf("%-20s%c", headers[i], 179); // Header and vertical line
    }
    printf("\n");

    // Print the header-row separator
    printf("%c", 195); // Left T-intersection
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", 196); // Horizontal line
        }
        if (i != 3) {
            printf("%c", 197); // T-intersection
        }
    }
    printf("%c\n", 180); // Right T-intersection

    // Print the table data
    for (int i = 0; i < 6; i++) {
        printf("%c", 179); // Vertical line
        for (int j = 0; j < 4; j++) {
            printf("%-20d%c", table[i][j], 179); // Data and vertical line
        }
        printf("\n");

        if (i != 5) {
            printf("%c", 195); // Left T-intersection
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 20; k++) {
                    printf("%c", 196); // Horizontal line
                }
                if (j != 3) {
                    printf("%c", 197); // T-intersection
                }
            }
            printf("%c\n", 180); // Right T-intersection
        }
    }

    // Print the bottom border
    printf("%c", 192); // Bottom-left corner
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", 196); // Horizontal line
        }
        if (i != 3) {
            printf("%c", 193); // Intersection
        }
    }
    printf("%c\n", 217); // Bottom-right corner

}

void setup(Process processes[], Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], int num){

    // Process processes[6];

    // initializeProcesses(processes, num);

    // printTable(processes);

    // for (int i = 0; i < num; i++)
    // {
    //     printf("PID: %d\n", processes[i].processId);
    //     printf("Arrival Time: %d\n", processes[i].arrivalTime);
    //     printf("Burst Time: %d\n", processes[i].burstTime);
    //     printf("Priority ID: %d\n", processes[i].priorityId);
    // }
    

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

void printInfo(Process processes[], int num){

    int sum, average;
    for (int i = 0; i < 6; i++)
    {
        sum += processes[i].waitingTime;
    }
    average = sum/num;
    printf("Average waiting time = %d\n", average);
    
}

int main(){

    int choice;
    int num = 6;

    Process processes[6];
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

        initializeProcesses(processes, num);
        setup(processes, fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, num);

        switch(choice) {
            case 1:
                printf("You chose FCFS\n");
                // printTable(processes);
                // calculate_fcfs(fcfs_processes, num);
                // calclulate_sjf(sjf_processes, num);
                // calclulate_srtf(srtf_processes, num);
                // calculate_rr(rr_processes, num, 5);
                // calculate_priority(priority_processes, num, 5);
                // printInfo(fcfs_processes, num);
                // printInfo(sjf_processes, num);
                // printInfo(srtf_processes, num);
                // printInfo(rr_processes, num);
                // printInfo(priority_processes, num);
                break;
            case 2:
                printf("You chose SJF\n");
                break;
            case 3:
                printf("You chose SRTF\n");
                break;
            case 4:
                printf("You chose RR\n");
                break;
            case 5:
                printf("You chose Priority\n");
                break;
            case 6:
                printf("Quitting program...\n");
                return 0;
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