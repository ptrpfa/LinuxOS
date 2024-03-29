#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

// CONST
#define NUM_PROC 6
#define BTUPPER 10
#define BTLOWER 3

// Structure definitions
typedef struct
{
    int processId;
    int priorityId;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
} Process;

typedef struct
{
    float turnaround_average;
    float waiting_average;
    float response_average;
    char * output;
} Algo;

// Setting Boundary for each algo
void initializeProcesses_FCFS(Process processes[], int num);
void initializeProcesses_SJF(Process processes[], int num);
void initializeProcesses_SRTF(Process processes[], int num);
void initializeProcesses_RR(Process processes[], int num);
void initializeProcesses_Priority(Process processes[], int num);
void setup(Process processes[], Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], int num);

// Misc
char* draw_gantt(int gantt[], int size);
void swap(Process *a, Process *b);
void sortProcesses(Process processes[], int num_process);
void print_to_file(int choice, Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int num);
void printTable(Process processes[]);
void printInfo(Process processes[], Algo *algo, int num, char type[]);
void calculate_algo(Process processes[], Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int num);

// Algorithm Functions
void calculate_for_fcfs(Process processes[], int num, Algo *fcfs_algo);
void calculate_fcfs(Process processes[], int num, Algo *fcfs_algo);
void calclulate_sjf(Process processes[], int num,Algo *sjf_algo);
void calclulate_srtf(Process processes[], int num,Algo *srtf_algo);
void calculate_for_rr(Process processes[], int num, int quantum,Algo *rr_algo);
void calculate_rr(Process processes[], int num, int quantum,Algo *rr_algo);
void calculate_priority(Process processes[], int num,Algo *priority_algo);

// Checking results
void checkFastestAlgorithms(Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int choice);
void checkFastestAlgorithms_file(FILE *file, Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int choice);


int main()
{

    // Initialize choice and number of processes into variables
    int choice;
    int num = NUM_PROC;

    // Initialize structs
    Process processes[NUM_PROC];
    Process fcfs_processes[NUM_PROC];
    Process sjf_processes[NUM_PROC];
    Process srtf_processes[NUM_PROC];
    Process rr_processes[NUM_PROC];
    Process priority_processes[NUM_PROC];

    Algo fcfs_algo;
    Algo sjf_algo;
    Algo srtf_algo;
    Algo rr_algo;
    Algo priority_algo;

    // Print program main menu
    printf("Welcome to CSC1107OS scheduling algorithm program!\n");
    printf("--------------------------------------------------\n");

    // Start of while loop to keep main menu running until quit
    while (1)
    {
        printf("Please select an option\n");
        printf("1) FCFS\n");
        printf("2) SJF\n");
        printf("3) SRTF\n");
        printf("4) RR\n");
        printf("5) Priority\n");
        printf("6) Quit\n");
        printf("Enter an option: ");

        scanf("%d", &choice); // Read user input

        while (choice < 1 || choice > 6)
        { // Check user input, if invalid input prompt user
            printf("Invalid input! Please enter a number between 1 and 6: ");
            scanf("%d", &choice); // Read user input again
            printf("\n");
        }

        switch (choice)
        {
        case 1:
            printf("You chose FCFS\n");
            initializeProcesses_FCFS(processes, num); // Initialize base process struct with a set of values that will allow the chosen algo to win
            break;
        case 2:
            printf("You chose SJF\n");
            initializeProcesses_SJF(processes, num);
            break;
        case 3:
            printf("You chose SRTF\n");
            initializeProcesses_SRTF(processes, num);
            break;
        case 4:
            printf("You chose RR\n");
            initializeProcesses_RR(processes, num);
            break;
        case 5:
            printf("You chose Priority\n");
            initializeProcesses_Priority(processes, num);
            break;
        case 6:
            printf("Quitting program...\n");
            return 0;
        }

        setup(processes, fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, num); // Assign base process generated values into all the algos
        printTable(processes); // Print the table to show generated burst, arrival, priority and quantum
        printf("QUANTUM used = 5\n\n");
        calculate_algo(processes, fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, &fcfs_algo, &sjf_algo, &srtf_algo, &rr_algo, &priority_algo, num);
        checkFastestAlgorithms(&fcfs_algo, &sjf_algo, &srtf_algo, &rr_algo, &priority_algo, choice);
        print_to_file(choice, fcfs_processes, sjf_processes, srtf_processes, rr_processes, priority_processes, &fcfs_algo, &sjf_algo, &srtf_algo, &rr_algo, &priority_algo, num);

    }
    return 0;
}

void initializeProcesses_FCFS(Process processes[], int num)
{

    int previousAT = 0;
    int previousBT = 0;
    int priorityId;

    // init
    srand(time(NULL));
    // Set process ID for first process
    processes[0].processId = 1;
    // Set burst time for first process
    processes[0].burstTime = ((rand() % (BTUPPER - BTLOWER + 1)) + BTLOWER);
    // Set arrival time for first process
    processes[0].arrivalTime = 0;
    // Set priority ID for first process
    processes[0].priorityId = rand() % BTUPPER;

    // For each of the process
    for (int i = 1; i < NUM_PROC; i++)
    {
        // Set Process ID
        processes[i].processId = i + 1;

        // Get prev burst time BT
        previousBT = processes[i - 1].burstTime;
        // Set current burst time
        processes[i].burstTime = ((rand() % (BTUPPER - previousBT + 1)) + previousBT);

        // Get prev arrival time AT
        previousAT = processes[i - 1].arrivalTime;
        // Set previous arrival time
        processes[i].arrivalTime = ((rand() % (BTUPPER - previousAT + 1)) + previousAT);

        // Set priority ID
        processes[i].priorityId = rand() % BTUPPER;
    }
}

void initializeProcesses_SJF(Process processes[], int num) {
    srand(time(NULL));

    int duplicateCount[15] = {0};

    processes[0].arrivalTime = 0;

    for (int i = 1; i < NUM_PROC; i++) {
        // Set process ID
        processes[i].processId = i + 1;

        // Set random arrival time
        int duplicateId;
        do{
            duplicateId = rand() % 15 + 1;
        } while (duplicateCount[duplicateId - 1] >= 1);

        processes[i].arrivalTime = duplicateId;
        duplicateCount[duplicateId - 1]++;

        // Set priority ID
        processes[i].priorityId = rand() % BTUPPER;
    }

    // Sort processes based on arrival time using bubble sort
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                // Swap processes
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Set burst time for each process
    for (int i = 0; i < num; i++) {
        // Set burst time for first process
        if (i == 0) {
            processes[0].burstTime = rand() % (BTUPPER - BTLOWER + 1) + BTLOWER;
        } else {
            int previousFT;
            int remainingTime;
            
            //Check if the arrival is duplcated
            if(processes[i].arrivalTime != processes[i-1].arrivalTime){
          
                previousFT = processes[i - 1].arrivalTime + processes[i - 1].burstTime;
                remainingTime = previousFT - processes[i].arrivalTime;

            }else{
                if(i != 1){
                    previousFT = processes[i - 2].arrivalTime + processes[i - 2].burstTime;
                    remainingTime = previousFT - processes[i].arrivalTime;
                }else{
                    previousFT = processes[i - 1].arrivalTime + processes[i - 1].burstTime;
                    remainingTime = previousFT - processes[i].arrivalTime;
                }
            }
            
            if (processes[i].arrivalTime < previousFT) {
                int value = BTUPPER - remainingTime + 1;
                if(value == 0 ){
                    processes[i].burstTime = (rand() % remainingTime) ;
                }else
                {
                    processes[i].burstTime = remainingTime + (rand() % value);
                    if(processes[i].arrivalTime != processes[i-1].arrivalTime){
                        processes[i].burstTime +=1;
                    }
                }
                processes[i].burstTime = processes[i].burstTime+1;
            } else {
                processes[i].burstTime = rand() % (BTUPPER - BTLOWER + 1) + BTLOWER;
            }
        }
    }
    
    Process backup[NUM_PROC];
    for (int i = 0; i < num; i++) {
        int id = processes[i].processId;
        backup[id - 1] = processes[i];
    }

    for (int i = 0; i < num; i++) {
        processes[i] = backup[i];
    }
}



void initializeProcesses_SRTF(Process processes[], int num)
{
    int priorityId;

    // init
    srand(time(NULL));
    // Set process ID for first process
    processes[0].processId = 1;
    // Set burst time for first process
    processes[0].burstTime = ((rand() % (BTUPPER - BTLOWER + 1)) + BTLOWER);
    // Set arrival time for first process
    processes[0].arrivalTime = 0;
    // Set priority ID for first process
    processes[0].priorityId = rand() % BTUPPER;

    // For each of the process
    for (int i = 1; i < NUM_PROC; i++)
    {
        // Set Process ID
        processes[i].processId = i + 1;

        // Set current burst time
        processes[i].burstTime = ((rand() % (BTUPPER - BTLOWER + 1)) + BTLOWER);

        // Set previous arrival time
        processes[i].arrivalTime = ((rand() % (BTUPPER - BTLOWER + 1)) + BTLOWER);

        // Set priority ID
        processes[i].priorityId = rand() % BTUPPER;
    }




}
void initializeProcesses_RR(Process processes[], int num)
{
    int burstTimes[NUM_PROC];

    // Generate random burst times
    for (int i = 0; i < NUM_PROC; i++)
    {
        burstTimes[i] = (rand() % BTUPPER) + 1;
    }

    // Sort burst times in ascending order
    for (int i = 0; i < NUM_PROC - 1; i++)
    {
        for (int j = 0; j < NUM_PROC - i - 1; j++)
        {
            if (burstTimes[j] > burstTimes[j + 1])
            {
                int temp = burstTimes[j];
                burstTimes[j] = burstTimes[j + 1];
                burstTimes[j + 1] = temp;
            }
        }
    }

    // Calculate median
    float median;
    if (NUM_PROC % 2 == 0)
    {
        median = (burstTimes[NUM_PROC / 2] + burstTimes[(NUM_PROC / 2) - 1]) / 2.0;
    }
    else
    {
        median = burstTimes[NUM_PROC / 2];
    }

    // Find the largest burst time
    int largestBurstTime = burstTimes[NUM_PROC - 1];

    // Calculate dynamic time quantum
    int quantum = (median + largestBurstTime) / 2;

    // Recalculate if quantum is greater than 5 so that the gantt chart can fit
    //this is because there is a constraint on our gantt chart
    while (quantum > 5)
    {
        // Generate random burst times
        for (int i = 0; i < NUM_PROC; i++)
        {
            burstTimes[i] = (rand() % BTUPPER) + 1;
        }

        // Sort burst times in ascending order
        for (int i = 0; i < NUM_PROC - 1; i++)
        {
            for (int j = 0; j < NUM_PROC - i - 1; j++)
            {
                if (burstTimes[j] > burstTimes[j + 1])
                {
                    int temp = burstTimes[j];
                    burstTimes[j] = burstTimes[j + 1];
                    burstTimes[j + 1] = temp;
                }
            }
        }

        // Recalculate median
        if (NUM_PROC % 2 == 0)
        {
            median = (burstTimes[NUM_PROC / 2] + burstTimes[(NUM_PROC / 2) - 1]) / 2.0;
        }
        else
        {
            median = burstTimes[NUM_PROC / 2];
        }

        // Find the largest burst time
        largestBurstTime = burstTimes[NUM_PROC - 1];

        // Recalculate quantum
        quantum = (median + largestBurstTime) / 2;
    }

    // Set process ID, arrival time, burst time, and priority ID
    processes[0].processId = 1;
    processes[0].arrivalTime = (rand() % 9) + 1;
    processes[0].burstTime = quantum * ((rand() % 3) + 1);
    processes[0].priorityId = rand() % BTUPPER;

    for (int i = 1; i < NUM_PROC; i++)
    {
        processes[i].processId = i + 1;
        processes[i].arrivalTime = processes[i - 1].arrivalTime + processes[i - 1].burstTime;
        processes[i].burstTime = quantum * ((rand() % 3) + 1);
        processes[i].priorityId = rand() % BTUPPER;
    }
}

void initializeProcesses_Priority(Process processes[], int num)
{

     int burstTimes[NUM_PROC];

    // Generate random burst times
    for (int i = 0; i < NUM_PROC; i++)
    {
        burstTimes[i] = (rand() % BTUPPER) + 1;
    }

    // Sort burst times in ascending order
    for (int i = 0; i < NUM_PROC - 1; i++)
    {
        for (int j = 0; j < NUM_PROC - i - 1; j++)
        {
            if (burstTimes[j] > burstTimes[j + 1])
            {
                int temp = burstTimes[j];
                burstTimes[j] = burstTimes[j + 1];
                burstTimes[j + 1] = temp;
            }
        }
    }
    
     processes[0].arrivalTime = 0;
     processes[0].burstTime = burstTimes[0];
     processes[0].priorityId = 1;  
     processes[0].processId = 1;

    // Assign priorities based on the sorted burst times
    for (int i = 1; i < NUM_PROC; i++) {
        // Set Process ID
        processes[i].processId = i + 1;
        // Assign priority in ascending order
        processes[i].priorityId = i + 1; 
        // Set the burst time for the process
        processes[i].burstTime = burstTimes[i]; 
        // Set previous arrival time
        processes[i].arrivalTime = ((rand() % (BTUPPER - processes[i-1].arrivalTime + 1)) + processes[i-1].arrivalTime);
        }
       
}

char* draw_gantt(int gantt[], int size)
{
    int count = 1;
    int previous = gantt[0];
    int time = 0;
    char* output = (char*)malloc(10000 * sizeof(char));
    int offset = 0;

    offset += sprintf(output + offset, "|");

    for (int i = 1; i < size; i++)
    {
        if (gantt[i] == previous)
        {
            count++;
        }
        else
        {
            for (int j = 0; j < count; j++)
            {
                offset += sprintf(output + offset, "-");
            }
            offset += sprintf(output + offset, "%d", previous);
            for (int j = 0; j < count; j++)
            {
                offset += sprintf(output + offset, "-");
            }
            offset += sprintf(output + offset, "|");
            time += count;
            count = 1;
        }
        previous = gantt[i];
    }

    for (int j = 0; j < count; j++)
    {
        offset += sprintf(output + offset, "-");
    }
    offset += sprintf(output + offset, "%d", previous);
    for (int j = 0; j < count; j++)
    {
        offset += sprintf(output + offset, "-");
    }
    offset += sprintf(output + offset, "|");
    offset += sprintf(output + offset, "\n");
    offset += sprintf(output + offset, "0");
    count = 1;
    time = 0;
    previous = gantt[0];

    for (int i = 1; i < size + 1; i++)
    {
        if (gantt[i] == previous)
        {
            count++;
        }
        else
        {
            time += count;
            if (time >= 10)
            {
                for (int j = 0; j < 2 * count; j++)
                {
                    offset += sprintf(output + offset, " ");
                }
                offset += sprintf(output + offset, "%d", time);
                count = 1;
            }
            else
            {
                for (int j = 0; j < 2 * count + 1; j++)
                {
                    offset += sprintf(output + offset, " ");
                }
                offset += sprintf(output + offset, "%d", time);
                count = 1;
            }
        }
        previous = gantt[i];
    }
    time += count;
    for (int j = 0; j < 2 * count; j++)
    {
        offset += sprintf(output + offset, " ");
    }

    printf("%s", output);

    return output;
}

// helper function for sorting to swap process positions in the array of structs
void swap(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// sort the array of structs based on arrival time through bubble sort algorithm
void sortProcesses(Process processes[], int num_process)
{
    for (int i = 0; i < num_process - 1; i++)
    {
        for (int j = 0; j < num_process - i - 1; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void calculate_for_fcfs(Process processes[], int num, Algo *fcfs_algo)
{

    int currentTime = 0; // initialize current time to 0

    int ganttBar[100];  // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0; i < num; i++)
    {
        while (currentTime < processes[i].arrivalTime)
        { // check that while the current time is < than the process arrival time, increment the current time as the process has not arrived
            ganttCount++;
            currentTime++;
        }
        processes[i].responseTime = currentTime - processes[i].arrivalTime; // assignment of response time
        currentTime += processes[i].burstTime;                              // add burst time to current time to finish process execution
        for (int j = 0; j < processes[i].burstTime; j++)
        {
            ganttBar[ganttCount] = processes[i].processId; // assign the number of seconds of burst time to the array index to keep track of the order execution of processes
            ganttCount++;
        }

        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;            // assignment of turnaround time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime; // assignment of waiting time
    }

    fcfs_algo->output = draw_gantt(ganttBar, ganttCount); // draw the gantt chart with a function
    //print_gantt(ganttBar,ganttCount);
    printf("\n");
}

// main function to sort and calculate the fcfs process details
void calculate_fcfs(Process processes[], int num, Algo *fcfs_algo)
{

    sortProcesses(processes, num);
    calculate_for_fcfs(processes, num, fcfs_algo);
}

void calclulate_sjf(Process processes[], int num, Algo *sjf_algo)
{

    int rt[num];        // initialize array to keep track of the remaining time left to execute a process
    int arrived[num];   // initialize array to keep track of which process has arrived
    int completed[num]; // initialize array to keep track of which process has been completed
    int flag = 0, shortest = -1, currentTime = 0, minimum = INT_MAX, finishTime = 0, complete = 0, occupied = 0, responseTime = 0;

    int ganttBar[100];  // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0; i < num; i++)
    {
        rt[i] = processes[i].burstTime; // assign the burst time of each process and represent them as the remaining time a process needs to run
        arrived[i] = 0;                 // set all index to 0 as no process has arrived yet
        completed[i] = 0;               // set all index to 0 as no process has been completed
    }

    while (complete != num)
    {

        for (int j = 0; j < num; j++)
        {
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0)
            {
                arrived[j] = 1; // if the process has arrived and the remaining time of it is not 0, set the process to 1
            }
        }

        for (int j = 0; j < num; j++)
        {
            if (arrived[j] == 1 && completed[j] != 1 && occupied == 0)
            { // if it has arrived and is not completed, and there are currently no processes executing, then proceed
                if (shortest == -1 || rt[j] < minimum || (rt[j] == minimum && processes[j].arrivalTime < processes[shortest].arrivalTime))
                {                               // check for the shortest remaining time of the processes that have arrived and are not completed, if there are 2 processes with the same remaining time that are the shortest, take the process that arrived earlier
                    flag = 1;                   // set the flag at a process is set to be executed
                    minimum = rt[j];            // assign a minimum so that the loop will be able to find the next minimum
                    shortest = j;               // assign shortest to the current process index
                    responseTime = currentTime; // assign response time to be the current time for calculation of the response time of the process to be completed later
                }
            }
        }

        if (flag == 1)
        {                                                         // if flag is 1, a process is to be executed
            occupied = 1;                                         // set occupied to 1 so that no other process can take over even if it has a shorter remaining time as it is non preemptive
            rt[shortest]--;                                       // reduce the remaining time of the current process by 1
            ganttBar[ganttCount] = processes[shortest].processId; // assign the current index of the gantt bar to the process ID of the currently executing process
            ganttCount++;
            currentTime++;
            if (rt[shortest] == 0)
            {                            // if remaining time is 0, process has finished executing
                complete++;              // increment complete variable by 1
                arrived[shortest] = 0;   // set the finish process to 0 in the arrived array
                completed[shortest] = 1; // set the finish process to 1 in the complete array
                finishTime = currentTime;
                minimum = INT_MAX;                                                                                    // set the minimum to max to allow the next minimum to be found later
                processes[shortest].turnaroundTime = finishTime - processes[shortest].arrivalTime;                    // assign turnaround time
                processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime; // assign waiting time
                processes[shortest].responseTime = responseTime - processes[shortest].arrivalTime;                    // assign response time
                occupied = 0;                                                                                         // set occupied to 0 to allow other process to be executed
                shortest = -1;                                                                                        // reset shortest variable
                flag = 0;                                                                                             // set flag to 0 as we do not know if there will be another process to be executed in the next second
            }
        }
        else
        { // if flag is 0, increase time as no process is ready to be executed
            ganttCount++;
            currentTime++;
        }
    }
    sjf_algo->output = draw_gantt(ganttBar, ganttCount);
    //print_gantt(ganttBar,ganttCount);
    printf("\n");
}

void calclulate_srtf(Process processes[], int num,Algo *srtf_algo)
{

    int rt[num];        // initialize array to keep track of the remaining time left to execute a process
    int arrived[num];   // initialize array to keep track of which process has arrived
    int completed[num]; // initialize array to keep track of which process has been completed
    int responded[num]; // initialize array to keep track of which process has been responded to
    int flag = 0, shortest = -1, currentTime = 0, minimum = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

    int ganttBar[100];  // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0; i < num; i++)
    {
        rt[i] = processes[i].burstTime; // assign the burst time of each process and represent them as the remaining time a process needs to run
        arrived[i] = 0;                 // set all index to 0 as no process has arrived yet
        completed[i] = 0;               // set all index to 0 as no process has been completed
        responded[i] = 0;               // set all index to 0 as no process has been responded to yet
    }

    while (complete != num)
    {

        for (int j = 0; j < num; j++)
        {
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0)
            {
                arrived[j] = 1; // if the process has arrived and the remaining time of it is not 0, set the process to 1
            }
        }

        for (int j = 0; j < num; j++)
        {
            if (arrived[j] == 1 && completed[j] != 1)
            { // if it has arrived and is not completed, then proceed
                if (shortest == -1 || rt[j] < minimum || (rt[j] == minimum && processes[j].arrivalTime < processes[shortest].arrivalTime))
                {                    // check for the shortest remaining time of the processes that have arrived and are not completed, if there are 2 processes with the same remaining time that are the shortest, take the process that arrived earlier
                    flag = 1;        // set the flag at a process is set to be executed
                    minimum = rt[j]; // assign a minimum so that the loop will be able to find the next minimum
                    shortest = j;    // assign shortest to the current process index
                }
            }
        }

        if (flag == 1)
        { // if flag is 1, a process is to be executed
            if (responded[shortest] == 0)
            { // if the current process has not be responded to yet, calculate the response time and assign it to the process struct
                responseTime = currentTime - processes[shortest].arrivalTime;
                processes[shortest].responseTime = responseTime;
                responded[shortest] = 1; // set the process to responded
            }
            rt[shortest]--;                                       // reduce the remaining time of the current process by 1
            ganttBar[ganttCount] = processes[shortest].processId; // assign the current index of the gantt bar to the process ID of the currently executing process
            ganttCount++;
            currentTime++;
            if (rt[shortest] == 0)
            {                            // if remaining time is 0, process has finished executing
                complete++;              // increment complete variable by 1
                arrived[shortest] = 0;   // set the finish process to 0 in the arrived array
                completed[shortest] = 1; // set the finish process to 1 in the complete array
                finishTime = currentTime;
                minimum = INT_MAX;                                                                                    // set the minimum to max to allow the next minimum to be found later
                processes[shortest].turnaroundTime = finishTime - processes[shortest].arrivalTime;                    // assign turnaround time
                processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime; // assign waiting time
                shortest = -1;                                                                                        // reset shortest variable
                flag = 0;                                                                                             // set flag to 0 as we do not know if there will be another process to be executed in the next second
            }
        }
        else
        { // if flag is 0, increase time as no process is ready to be executed
            ganttCount++;
            currentTime++;
        }
    }

    srtf_algo->output = draw_gantt(ganttBar, ganttCount);
    //print_gantt(ganttBar,ganttCount);
    printf("\n");
}

void calculate_for_rr(Process processes[], int num, int quantum,Algo *rr_algo)
{
    int rt[num];           // initialize array to keep track of the remaining time left to execute a process
    int responseFlag[num]; // initialize array to keep track of which process has been responded to
    int currentTime = 0, finishTime = 0, complete = 0;

    int ganttBar[100];  // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0; i < num; i++)
    {
        rt[i] = processes[i].burstTime; // assign the burst time of each process and represent them as the remaining time a process needs to run
        responseFlag[i] = 0;            // set all index to 0 as no process has been responded to yet
    }

    while (complete != num)
    {
        int flag = 0; // set flag to 0 as no process is set to run yet
        for (int j = 0; j < num; j++)
        {
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0)
            {             // if it has arrived and is not completed, then proceed
                flag = 1; // process has arrived, set flag to run as a new process is expected to run
                if (responseFlag[j] == 0)
                { // if the current process has not be responded to yet, calculate the response time and assign it to the process struct
                    processes[j].responseTime = currentTime - processes[j].arrivalTime;
                    responseFlag[j] = 1; // set the process to responded
                }
                if (rt[j] > quantum)
                { // check if remaining time of process is more than quantum
                    rt[j] -= quantum;
                    for (int i = 0; i < quantum; i++)
                    {
                        ganttBar[ganttCount] = processes[j].processId; // assign the number of seconds of quantum to the array index to keep track of the order execution of processes
                        ganttCount++;
                    }

                    currentTime += quantum; // increment current time by quantum
                }
                else
                {
                    currentTime += rt[j]; // if rt <= quantum, increment current time by remaining time of the process left to execute
                    for (int i = 0; i < rt[j]; i++)
                    {
                        ganttBar[ganttCount] = processes[j].processId; // assign the number of seconds of remaining time to the array index to keep track of the order execution of processes
                        ganttCount++;
                    }

                    rt[j] = 0; // set remaining time to 0
                    finishTime = currentTime;
                    processes[j].turnaroundTime = finishTime - processes[j].arrivalTime;             // assign turnaround time
                    processes[j].waitingTime = processes[j].turnaroundTime - processes[j].burstTime; // assign waiting time
                    complete++;
                }
            }
        }
        if (flag == 0)
        { // if flag is 0, increase time as no process is ready to be executed
            ganttCount++;
            currentTime++;
        }
    }

    rr_algo->output = draw_gantt(ganttBar, ganttCount);
    //print_gantt(ganttBar,ganttCount);
    printf("\n");
}

// main function to sort and calculate the rr process details
void calculate_rr(Process processes[], int num, int quantum,Algo *rr_algo)
{

    sortProcesses(processes, num);
    calculate_for_rr(processes, num, quantum, rr_algo);
}

void calculate_priority(Process processes[], int num,Algo *priority_algo)
{

    int rt[num];        // initialize array to keep track of the remaining time left to execute a process
    int priority[num];  // initialize array to keep track of priority of processes
    int arrived[num];   // initialize array to keep track of which process has arrived
    int completed[num]; // initialize array to keep track of which process has been completed
    int responded[num]; // initialize array to keep track of which process has been responded to
    int flag = 0, priorityIndex = -1, currentTime = 0, highest_priority = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

    int ganttBar[100];  // initialize an array of size 100 to keep track of the order of process execution
    int ganttCount = 0; // counter to keep track of the current order to help with assignment of process ID to the index of the ganttBar array

    for (int i = 0; i < 100; i++)
    {
        ganttBar[i] = 0; // set all index of the array to 0, 0 represents that no processes are running at that time
    }

    for (int i = 0; i < num; i++)
    {
        rt[i] = processes[i].burstTime;        // assign the burst time of each process and represent them as the remaining time a process needs to run
        priority[i] = processes[i].priorityId; // assign the priority of each process to the array
        arrived[i] = 0;                        // set all index to 0 as no process has arrived yet
        completed[i] = 0;                      // set all index to 0 as no process has been completed
        responded[i] = 0;                      // set all index to 0 as no process has been responded to yet
    }

    while (complete != num)
    { // while there are still processes to be completed, keep on running

        for (int j = 0; j < num; j++)
        {
            if (processes[j].arrivalTime <= currentTime && rt[j] != 0)
            {
                arrived[j] = 1; // if the process has arrived and the remaining time of it is not 0, set the process to 1
            }
        }

        for (int j = 0; j < num; j++)
        {
            if (arrived[j] == 1 && completed[j] != 1)
            { // if it has arrived and is not completed, then proceed
                if (priorityIndex == -1 || priority[j] < highest_priority || (priority[j] == highest_priority && processes[j].arrivalTime < processes[priorityIndex].arrivalTime))
                {                                   // check for the highest priority of the processes that have arrived and are not completed, if there are 2 processes with the same priority, take the process that arrived earlier
                    flag = 1;                       // set the flag at a process is set to be executed
                    highest_priority = priority[j]; // assign a highest priority so that the loop will be able to find the next highest priority
                    priorityIndex = j;              // assign the priority index to the current process index
                }
            }
        }

        if (flag == 1)
        { // if flag is 1, a process is to be executed
            if (responded[priorityIndex] == 0)
            { // if the current process has not be responded to yet, calculate the response time and assign it to the process struct
                responseTime = currentTime - processes[priorityIndex].arrivalTime;
                processes[priorityIndex].responseTime = responseTime;
                responded[priorityIndex] = 1; // set the process to responded
            }
            rt[priorityIndex]--;                                       // reduce the remaining time of the current process by 1
            ganttBar[ganttCount] = processes[priorityIndex].processId; // assign the current index of the gantt bar to the process ID of the currently executing process
            ganttCount++;
            currentTime++;
            if (rt[priorityIndex] == 0)
            {                                 // if remaining time is 0, process has finished executing
                complete++;                   // increment complete variable by 1
                arrived[priorityIndex] = 0;   // set the finish process to 0 in the arrived array
                completed[priorityIndex] = 1; // set the finish process to 1 in the complete array
                finishTime = currentTime;
                highest_priority = INT_MAX;                                                                                          // set the highest priority to max to allow the next priority to be found later
                processes[priorityIndex].turnaroundTime = finishTime - processes[priorityIndex].arrivalTime;                         // assign turnaround time
                processes[priorityIndex].waitingTime = processes[priorityIndex].turnaroundTime - processes[priorityIndex].burstTime; // assign waiting time
                priorityIndex = -1;                                                                                                  // reset priority index variable
                flag = 0;                                                                                                            // set flag to 0 as we do not know if there will be another process to be executed in the next second
            }
        }
        else
        { // if flag is 0, increase time as no process is ready to be executed
            ganttCount++;
            currentTime++;
        }
    }

    priority_algo->output = draw_gantt(ganttBar, ganttCount);
    printf("\n");
}



void print_to_file(int choice, Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int num)
{
    /*
    This function initializes a file pointer to use fprintf to write the process details into our .txt file
    We pass in our process structs into the function so that we can read their details and display them using fprintf into the .txt file
    */

    FILE *file;

    file = fopen("Q2_Group_2.txt", "w"); //Open the file in the directory, if file does not exist, create the file 

    if (file == NULL)
    {
        printf("Error opening the file.\n");
    }
    /*
    Start writing into the file, for each algorithm type
    Print the title of the algorithm
    Print the gantt chart
    Print the process details for each 6 processes
    Print the details of the average performance for turnaround, waiting and response time
    */
    fprintf(file, "FCFS processes\n"); //Print title
    fprintf(file, "%s", fcfs_algo->output); //Print gantt chart
    fprintf(file, "\n");
    fprintf(file, "\n");
    for (int i = 0; i < num; i++) //Print details for each of the 6 processes
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", fcfs_processes[i].processId, fcfs_processes[i].turnaroundTime, fcfs_processes[i].waitingTime, fcfs_processes[i].responseTime);
    }
    //Print the details of the average performance
    fprintf(file, "Average turnaround time for FCFS = %.2f\n", fcfs_algo->turnaround_average);
    fprintf(file, "Average waiting time for FCFS = %.2f\n", fcfs_algo->waiting_average);
    fprintf(file, "Average response time for FCFS = %.2f\n", fcfs_algo->response_average);
    fprintf(file, "\n");

    fprintf(file, "SJF processes\n");
    fprintf(file, "%s", sjf_algo->output);   
    fprintf(file, "\n");
    fprintf(file, "\n");

    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", sjf_processes[i].processId, sjf_processes[i].turnaroundTime, sjf_processes[i].waitingTime, sjf_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for SJF = %.2f\n", sjf_algo->turnaround_average);
    fprintf(file, "Average waiting time for SJF = %.2f\n", sjf_algo->waiting_average);
    fprintf(file, "Average response time for SJF = %.2f\n", sjf_algo->response_average);
    fprintf(file, "\n\n");

    fprintf(file, "SRTF processes\n");
    fprintf(file, "%s", srtf_algo->output);   
    fprintf(file, "\n");
    fprintf(file, "\n");

    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", srtf_processes[i].processId, srtf_processes[i].turnaroundTime, srtf_processes[i].waitingTime, srtf_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for SRTF = %.2f\n", srtf_algo->turnaround_average);
    fprintf(file, "Average waiting time for SRTF = %.2f\n", srtf_algo->waiting_average);
    fprintf(file, "Average response time for SRTF = %.2f\n", srtf_algo->response_average);
    fprintf(file, "\n");

    fprintf(file, "RR processes\n");
    fprintf(file, "%s", rr_algo->output);   
    fprintf(file, "\n");
    fprintf(file, "\n");

    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", rr_processes[i].processId, rr_processes[i].turnaroundTime, rr_processes[i].waitingTime, rr_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for RR = %.2f\n", rr_algo->turnaround_average);
    fprintf(file, "Average waiting time for RR = %.2f\n", rr_algo->waiting_average);
    fprintf(file, "Average response time for RR = %.2f\n", rr_algo->response_average);
    fprintf(file, "\n");

    fprintf(file, "Priority processes\n");
    fprintf(file, "%s", priority_algo->output);   
    fprintf(file, "\n");
    fprintf(file, "\n");

    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", priority_processes[i].processId, priority_processes[i].turnaroundTime, priority_processes[i].waitingTime, priority_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for PRIORITY = %.2f\n", priority_algo->turnaround_average);
    fprintf(file, "Average waiting time for PRIORITY = %.2f\n", priority_algo->waiting_average);
    fprintf(file, "Average response time for PRIORITY = %.2f\n", priority_algo->response_average);
    fprintf(file, "\n");
    
    //Invoke the function to find the fastest algorithm and display it at the bottom of the .txt file
    checkFastestAlgorithms_file(file, fcfs_algo, sjf_algo, srtf_algo, rr_algo, priority_algo, choice);
 
    fclose(file); //Close the file
}

void checkFastestAlgorithms(Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int choice)
{
    // Check fastest average turnaround time
    float fastest_turnaround = fcfs_algo->turnaround_average;
    char fastest_turnaround_algo[20] = "FCFS";

    /*
    Compare each algorithm with the fastest average turnaround time against each other
    If the average time for that algo is faster, the fastest algo will update
    If the algo is equally as fast and the choice is == to what the user has chosen, the chosen winner displayed will be what the user chose
    This is to account for situations where the algorithm has tied with other algorithms, if more than 1 algorithm has the same time and is the fastest, we will display the user's chosen algorithm as the fastest
    */
    if (sjf_algo->turnaround_average < fastest_turnaround || (sjf_algo->turnaround_average == fastest_turnaround && choice == 2)) // Compare and check
    {
        fastest_turnaround = sjf_algo->turnaround_average; // Assign new fastest
        strcpy(fastest_turnaround_algo, "SJF"); // Overwrite fastest algo char variable
    }

    if (srtf_algo->turnaround_average < fastest_turnaround || (srtf_algo->turnaround_average == fastest_turnaround && choice == 3))
    {
        fastest_turnaround = srtf_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "SRTF");
    }

    if (rr_algo->turnaround_average < fastest_turnaround || (rr_algo->turnaround_average == fastest_turnaround && choice == 4))
    {
        fastest_turnaround = rr_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "RR");
    }

    if (priority_algo->turnaround_average < fastest_turnaround || (priority_algo->turnaround_average == fastest_turnaround && choice == 5))
    {
        fastest_turnaround = priority_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "Priority");
    }

    printf("Algorithm with fastest average turnaround time: %s\n", fastest_turnaround_algo);
    printf("Fastest average turnaround time: %.2f\n", fastest_turnaround);
    printf("\n");

    // Check fastest average waiting time
    float fastest_waiting = fcfs_algo->waiting_average;
    char fastest_waiting_algo[20] = "FCFS";

    if (sjf_algo->waiting_average < fastest_waiting || (sjf_algo->waiting_average == fastest_waiting && choice == 2))
    {
        fastest_waiting = sjf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SJF");
    }

    if (srtf_algo->waiting_average < fastest_waiting || (srtf_algo->waiting_average == fastest_waiting && choice == 3))
    {
        fastest_waiting = srtf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SRTF");
    }

    if (rr_algo->waiting_average < fastest_waiting || (rr_algo->waiting_average == fastest_waiting && choice == 4))
    {
        fastest_waiting = rr_algo->waiting_average;
        strcpy(fastest_waiting_algo, "RR");
    }

    if (priority_algo->waiting_average < fastest_waiting || (priority_algo->waiting_average == fastest_waiting && choice == 5))
    {
        fastest_waiting = priority_algo->waiting_average;
        strcpy(fastest_waiting_algo, "Priority");
    }

    printf("Algorithm with fastest average waiting time: %s\n", fastest_waiting_algo);
    printf("Fastest average waiting time: %.2f\n", fastest_waiting);
    printf("\n");

    // Check fastest average response time
    float fastest_response = fcfs_algo->response_average;
    char fastest_response_algo[20] = "FCFS";

    if (sjf_algo->response_average < fastest_response || (sjf_algo->response_average == fastest_response && choice == 2))
    {
        fastest_response = sjf_algo->response_average;
        strcpy(fastest_response_algo, "SJF");
    }

    if (srtf_algo->response_average < fastest_response || (srtf_algo->response_average == fastest_response && choice == 3))
    {
        fastest_response = srtf_algo->response_average;
        strcpy(fastest_response_algo, "SRTF");
    }

    if (rr_algo->response_average < fastest_response || (rr_algo->response_average == fastest_response && choice == 4))
    {
        fastest_response = rr_algo->response_average;
        strcpy(fastest_response_algo, "RR");
    }

    if (priority_algo->response_average < fastest_response || (priority_algo->response_average == fastest_response && choice == 5))
    {
        fastest_response = priority_algo->response_average;
        strcpy(fastest_response_algo, "Priority");
    }

    printf("Algorithm with fastest average response time: %s\n", fastest_response_algo);
    printf("Fastest average response time: %.2f\n", fastest_response);
    printf("\n");
}

void checkFastestAlgorithms_file(FILE *file, Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int choice)
{
    // Check fastest average turnaround time
    float fastest_turnaround = fcfs_algo->turnaround_average;
    char fastest_turnaround_algo[20] = "FCFS";

    /*
    This time we use the same function, but we use fprintf to write to the file instead of printf
    We also pass in the file pointer to allow the program to write to the file
    */
    if (sjf_algo->turnaround_average < fastest_turnaround || (sjf_algo->turnaround_average == fastest_turnaround && choice == 2))
    {
        fastest_turnaround = sjf_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "SJF");
    }

    if (srtf_algo->turnaround_average < fastest_turnaround || (srtf_algo->turnaround_average == fastest_turnaround && choice == 3))
    {
        fastest_turnaround = srtf_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "SRTF");
    }

    if (rr_algo->turnaround_average < fastest_turnaround || (rr_algo->turnaround_average == fastest_turnaround && choice == 4))
    {
        fastest_turnaround = rr_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "RR");
    }

    if (priority_algo->turnaround_average < fastest_turnaround || (priority_algo->turnaround_average == fastest_turnaround && choice == 5))
    {
        fastest_turnaround = priority_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "Priority");
    }

    fprintf(file, "Algorithm with fastest average turnaround time: %s\n", fastest_turnaround_algo);
    fprintf(file, "Fastest average turnaround time: %.2f\n", fastest_turnaround);
    fprintf(file, "\n");

    // Check fastest average waiting time
    float fastest_waiting = fcfs_algo->waiting_average;
    char fastest_waiting_algo[20] = "FCFS";

    if (sjf_algo->waiting_average < fastest_waiting || (sjf_algo->waiting_average == fastest_waiting && choice == 2))
    {
        fastest_waiting = sjf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SJF");
    }

    if (srtf_algo->waiting_average < fastest_waiting || (srtf_algo->waiting_average == fastest_waiting && choice == 3))
    {
        fastest_waiting = srtf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SRTF");
    }

    if (rr_algo->waiting_average < fastest_waiting || (rr_algo->waiting_average == fastest_waiting && choice == 4))
    {
        fastest_waiting = rr_algo->waiting_average;
        strcpy(fastest_waiting_algo, "RR");
    }

    if (priority_algo->waiting_average < fastest_waiting || (priority_algo->waiting_average == fastest_waiting && choice == 5))
    {
        fastest_waiting = priority_algo->waiting_average;
        strcpy(fastest_waiting_algo, "Priority");
    }

    fprintf(file, "Algorithm with fastest average waiting time: %s\n", fastest_waiting_algo);
    fprintf(file, "Fastest average waiting time: %.2f\n", fastest_waiting);
    fprintf(file, "\n");

    // Check fastest average response time
    float fastest_response = fcfs_algo->response_average;
    char fastest_response_algo[20] = "FCFS";

    if (sjf_algo->response_average < fastest_response || (sjf_algo->response_average == fastest_response && choice == 2))
    {
        fastest_response = sjf_algo->response_average;
        strcpy(fastest_response_algo, "SJF");
    }

    if (srtf_algo->response_average < fastest_response || (srtf_algo->response_average == fastest_response && choice == 3))
    {
        fastest_response = srtf_algo->response_average;
        strcpy(fastest_response_algo, "SRTF");
    }

    if (rr_algo->response_average < fastest_response || (rr_algo->response_average == fastest_response && choice == 4))
    {
        fastest_response = rr_algo->response_average;
        strcpy(fastest_response_algo, "RR");
    }

    if (priority_algo->response_average < fastest_response || (priority_algo->response_average == fastest_response && choice == 5))
    {
        fastest_response = priority_algo->response_average;
        strcpy(fastest_response_algo, "Priority");
    }

    fprintf(file, "Algorithm with fastest average response time: %s\n", fastest_response_algo);
    fprintf(file, "Fastest average response time: %.2f\n", fastest_response);
    fprintf(file, "\n");
}

void printTable(Process processes[])
{
    // Set the header names for the 4 columns
    char headers[4][20] = {
        "Process ID",
        "Arrival Time",
        "Burst Time",
        "Priority"};
    // Initialize 2d array table
    int table[6][4];

    // Assign process values to table
    for (int i = 0; i < 6; i++)
    {
        int j = 0;
        table[i][j] = processes[i].processId;
        table[i][j + 1] = processes[i].arrivalTime;
        table[i][j + 2] = processes[i].burstTime;
        table[i][j + 3] = processes[i].priorityId;
    }

    /*
    This function makes use of ASCII characters to print our table nicely into the CLI
    All the numbers use are ASCII codes for printing a certain part of the table
    */

    // Print the top border

    printf("%c", 218); // Top-left corner
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%c", 196); // Horizontal line
        }
        if (i != 3)
        {
            printf("%c", 194); // Intersection
        }
    }
    printf("%c\n", 191); // Top-right corner

    // Print the headers

    printf("%c", 179); // Vertical line
    for (int i = 0; i < 4; i++)
    {
        printf("%-20s%c", headers[i], 179); // Header and vertical line
    }
    printf("\n");

    // Print the header-row separator

    printf("%c", 195); // Left T-intersection
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%c", 196); // Horizontal line
        }
        if (i != 3)
        {
            printf("%c", 197); // T-intersection
        }
    }
    printf("%c\n", 180); // Right T-intersection

    // Print the table data

    for (int i = 0; i < 6; i++)
    {
        printf("%c", 179); // Vertical line
        for (int j = 0; j < 4; j++)
        {
            printf("%-20d%c", table[i][j], 179); // Data and vertical line
        }
        printf("\n");

        if (i != 5)
        {
            printf("%c", 195); // Left T-intersection
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 20; k++)
                {
                    printf("%c", 196); // Horizontal line
                }
                if (j != 3)
                {
                    printf("%c", 197); // T-intersection
                }
            }
            printf("%c\n", 180); // Right T-intersection
        }
    }

    // Print the bottom border

    printf("%c", 192); // Bottom-left corner
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%c", 196); // Horizontal line
        }
        if (i != 3)
        {
            printf("%c", 193); // Intersection
        }
    }
    printf("%c\n", 217); // Bottom-right corner
}

void setup(Process processes[], Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], int num)
{

    // Assign each processes processId, arrival time, burst time and priorityId to the generated values from the base process struct
    for (int i = 0; i < num; i++)
    {
        fcfs_processes[i].processId = processes[i].processId;     // assign fcfs processes process ID to base process process id
        fcfs_processes[i].arrivalTime = processes[i].arrivalTime; // assign fcfs processes arrival time to base process arrival time
        fcfs_processes[i].burstTime = processes[i].burstTime;     // assign fcfs processes burst time to base process burst time
        fcfs_processes[i].priorityId = processes[i].priorityId;   // assign fcfs processes priority ID to base process priority ID

        sjf_processes[i].processId = processes[i].processId;     // assign sjf processes process ID to base process process id
        sjf_processes[i].arrivalTime = processes[i].arrivalTime; // assign sjf processes arrival time to base process arrival time
        sjf_processes[i].burstTime = processes[i].burstTime;     // assign sjf processes burst time to base process burst time
        sjf_processes[i].priorityId = processes[i].priorityId;   // assign sjf processes priority ID to base process priority ID

        srtf_processes[i].processId = processes[i].processId;     // assign srtf processes process ID to base process process id
        srtf_processes[i].arrivalTime = processes[i].arrivalTime; // assign srtf processes arrival time to base process arrival time
        srtf_processes[i].burstTime = processes[i].burstTime;     // assign srtf processes burst time to base process burst time
        srtf_processes[i].priorityId = processes[i].priorityId;   // assign srtf processes priority ID to base process priority ID

        rr_processes[i].processId = processes[i].processId;     // assign rr processes process ID to base process process id
        rr_processes[i].arrivalTime = processes[i].arrivalTime; // assign rr processes arrival time to base process arrival time
        rr_processes[i].burstTime = processes[i].burstTime;     // assign rr processes burst time to base process burst time
        rr_processes[i].priorityId = processes[i].priorityId;   // assign rr processes priority ID to base process priority ID

        priority_processes[i].processId = processes[i].processId;     // assign priority processes process ID to base process process id
        priority_processes[i].arrivalTime = processes[i].arrivalTime; // assign priority processes arrival time to base process arrival time
        priority_processes[i].burstTime = processes[i].burstTime;     // assign priority processes burst time to base process burst time
        priority_processes[i].priorityId = processes[i].priorityId;   // assign priority processes priority ID to base process priority ID
    }
}

void printInfo(Process processes[], Algo *algo, int num, char type[])
{

    int turnaround_sum = 0, waiting_sum = 0, response_sum = 0;
    // Calculation of the total turnaround, waiting and response time for the set of processes passed into the arguments
    for (int i = 0; i < 6; i++)
    {
        turnaround_sum += processes[i].turnaroundTime; // add all process turnaround time to sum of turnaround time
        waiting_sum += processes[i].waitingTime;       // add all process waiting time to sum of waiting time
        response_sum += processes[i].responseTime;     // add all process response time to sum of response time
    }
    // Calculate the average timings and assign them into the struct that will hold information on the performance of an algorithm
    algo->turnaround_average = (float)turnaround_sum / num; // divide sum of turnaround time by number of processes to get average turnaround time
    algo->waiting_average = (float)waiting_sum / num;       // divide sum of waiting time by number of processes to get average waiting time
    algo->response_average = (float)response_sum / num;     // divide sum of response time by number of processes to get average response time
    // Print the type of algo
    printf("%s processes\n", type);
    // Print the details of each process
    for (int i = 0; i < num; i++)
    {
        printf("PID: %d Turnaround Time: %d Waiting Time: %d Response Time: %d\n", processes[i].processId, processes[i].turnaroundTime, processes[i].waitingTime, processes[i].responseTime);
    }
    // Print the performance details of the algo
    printf("Average turnaround time for %s = %.2f\n", type, algo->turnaround_average);
    printf("Average waiting time for %s = %.2f\n", type, algo->waiting_average);
    printf("Average response time for %s = %.2f\n", type, algo->response_average);
    printf("\n");
}

void calculate_algo(Process processes[], Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int num)
{

    // Perform function call for each algo for calculation by passing each struct array into each specific function
    // Each function will ammend each process in the struct array and calculate the turnaround, waiting and response for each process
    // Each process struct will have the updated turnaround, waiting and response time after the function call
    // Invoke printInfo to print the details of set of process
    printf("FCFS gantt chart\n");
    calculate_fcfs(fcfs_processes, num, fcfs_algo);
    printInfo(fcfs_processes, fcfs_algo, num, "FCFS");
    printf("SJF gantt chart\n");
    calclulate_sjf(sjf_processes, num , sjf_algo);
    printInfo(sjf_processes, sjf_algo, num, "SJF");
    printf("SRTF gantt chart\n");
    calclulate_srtf(srtf_processes, num , srtf_algo);
    printInfo(srtf_processes, srtf_algo, num, "SRTF");
    printf("RR gantt chart\n");
    calculate_rr(rr_processes, num, 5, rr_algo);
    printInfo(rr_processes, rr_algo, num, "RR");
    printf("PRIORITY gantt chart\n");
    calculate_priority(priority_processes, num , priority_algo);
    printInfo(priority_processes, priority_algo, num, "PRIORITY");
}