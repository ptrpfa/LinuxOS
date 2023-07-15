#include <stdio.h>
#include <limits.h>
#include "Schedule.h"

void printTable(Process processes[6]){
    // Set the header names for the 4 columns
    char headers[4][20] = {
        "Process ID",
        "Arrival Time",
        "Burst Time",
        "Priority"
    };
    // Initialize 2d array table
    int table[6][4];

    // Assign process values to table
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

    //Assign each processes processId, arrival time, burst time and priorityId to the generated values from the base process struct
    for (int i = 0; i < num; i++)
    {
        fcfs_processes[i].processId = processes[i].processId; //assign fcfs processes process ID to base process process id
        fcfs_processes[i].arrivalTime = processes[i].arrivalTime; //assign fcfs processes arrival time to base process arrival time
        fcfs_processes[i].burstTime = processes[i].burstTime; //assign fcfs processes burst time to base process burst time
        fcfs_processes[i].priorityId = processes[i].priorityId; //assign fcfs processes priority ID to base process priority ID

        sjf_processes[i].processId = processes[i].processId; //assign sjf processes process ID to base process process id
        sjf_processes[i].arrivalTime = processes[i].arrivalTime; //assign sjf processes arrival time to base process arrival time
        sjf_processes[i].burstTime = processes[i].burstTime; //assign sjf processes burst time to base process burst time
        sjf_processes[i].priorityId = processes[i].priorityId; //assign sjf processes priority ID to base process priority ID

        srtf_processes[i].processId = processes[i].processId; //assign srtf processes process ID to base process process id
        srtf_processes[i].arrivalTime = processes[i].arrivalTime; //assign srtf processes arrival time to base process arrival time
        srtf_processes[i].burstTime = processes[i].burstTime; //assign srtf processes burst time to base process burst time
        srtf_processes[i].priorityId = processes[i].priorityId; //assign srtf processes priority ID to base process priority ID

        rr_processes[i].processId = processes[i].processId; //assign rr processes process ID to base process process id
        rr_processes[i].arrivalTime = processes[i].arrivalTime; //assign rr processes arrival time to base process arrival time
        rr_processes[i].burstTime = processes[i].burstTime; //assign rr processes burst time to base process burst time
        rr_processes[i].priorityId = processes[i].priorityId; //assign rr processes priority ID to base process priority ID

        priority_processes[i].processId = processes[i].processId; //assign priority processes process ID to base process process id
        priority_processes[i].arrivalTime = processes[i].arrivalTime; //assign priority processes arrival time to base process arrival time
        priority_processes[i].burstTime = processes[i].burstTime; //assign priority processes burst time to base process burst time
        priority_processes[i].priorityId = processes[i].priorityId; //assign priority processes priority ID to base process priority ID
    }
    

}

void printInfo(Process processes[], Algo *algo, int num, char type[]){

    int turnaround_sum = 0, waiting_sum = 0, response_sum = 0;
    //Calculation of the total turnaround, waiting and response time for the set of processes passed into the arguments
    for (int i = 0; i < 6; i++)
    {
        turnaround_sum += processes[i].turnaroundTime; // add all process turnaround time to sum of turnaround time
        waiting_sum += processes[i].waitingTime; // add all process waiting time to sum of waiting time
        response_sum += processes[i].responseTime; // add all process response time to sum of response time

    }
    //Calculate the average timings and assign them into the struct that will hold information on the performance of an algorithm
    algo->turnaround_average = (float)turnaround_sum / num; // divide sum of turnaround time by number of processes to get average turnaround time
    algo->waiting_average = (float)waiting_sum / num; // divide sum of waiting time by number of processes to get average waiting time
    algo->response_average = (float)response_sum / num; // divide sum of response time by number of processes to get average response time
    //Print the type of algo
    printf("%s processes\n", type);
    //Print the details of each process
    for (int i = 0; i < num; i++)
    {
        printf("PID: %d Turnaround Time: %d Waiting Time: %d Response Time: %d\n", processes[i].processId, processes[i].turnaroundTime, processes[i].waitingTime, processes[i].responseTime);
    }
    //Print the performance details of the algo
    printf("Average turnaround time for %s = %.2f\n", type, algo->turnaround_average);
    printf("Average waiting time for %s = %.2f\n", type, algo->waiting_average);
    printf("Average response time for %s = %.2f\n", type, algo->response_average);
    printf("\n");
}

void calculate_algo(Process processes[], Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int num){

    //Perform function call for each algo for calculation by passing each struct array into each specific function
    //Each function will ammend each process in the struct array and calculate the turnaround, waiting and response for each process
    //Each process struct will have the updated turnaround, waiting and response time after the function call
    //Invoke printInfo to print the details of set of process
    printf("FCFS gantt chart\n");
    calculate_fcfs(fcfs_processes, num);
    printInfo(fcfs_processes, fcfs_algo, num, "FCFS");
    printf("SJF gantt chart\n");
    calclulate_sjf(sjf_processes, num);
    printInfo(sjf_processes, sjf_algo, num, "SJF");
    printf("SRTF gantt chart\n");
    calclulate_srtf(srtf_processes, num);
    printInfo(srtf_processes, srtf_algo, num, "SRTF");
    printf("RR gantt chart\n");
    calculate_rr(rr_processes, num, 5);
    printInfo(rr_processes, rr_algo, num, "RR");
    printf("PRIORITY gantt chart\n");
    calculate_priority(priority_processes, num);
    printInfo(priority_processes, priority_algo, num, "PRIORITY");

}

int main(){

    //Initialize choice and number of processes into variables
    int choice;
    int num = 6;

    //Initialize structs
    Process processes[6];
    Process fcfs_processes[6];
    Process sjf_processes[6];
    Process srtf_processes[6];
    Process rr_processes[6];
    Process priority_processes[6];

    Algo fcfs_algo;
    Algo sjf_algo;
    Algo srtf_algo;
    Algo rr_algo;
    Algo priority_algo;

    //Print program main menu
    printf("Welcome to CSC1107OS scheduling algorithm program!\n");
    printf("--------------------------------------------------\n");

    //Start of while loop to keep main menu running until quit
    while(1){
        printf("Please select an option\n");
        printf("1) FCFS\n");
        printf("2) SJF\n");
        printf("3) SRTF\n");
        printf("4) RR\n");
        printf("5) Priority\n");
        printf("6) Quit\n");
        printf("Enter an option: ");

        scanf("%d", &choice); //Read user input

        while(choice < 1 || choice > 6){ //Check user input, if invalid input prompt user
            printf("Invalid input! Please enter a number between 1 and 6: ");
            scanf("%d", &choice); //Read user input again
            printf("\n");
        }

        switch(choice) {
            case 1:
                printf("You chose FCFS\n");
                initializeProcesses(processes, num); //Initialize base process struct with a set of values that will allow the chosen algo to win
                setup(processes, fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, num); //Assign base process generated values into all the algos
                printTable(processes); //Print the table to show generated burst, arrival, priority and quantam
                calculate_algo(processes, fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, &fcfs_algo, &sjf_algo, &srtf_algo, &rr_algo, &priority_algo, num);
                checkFastestAlgorithms(&fcfs_algo, &sjf_algo, &srtf_algo, &rr_algo, &priority_algo);
                printing(fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, &fcfs_algo, &sjf_algo, &srtf_algo, &rr_algo, &priority_algo, num);
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