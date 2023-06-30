#include <stdio.h>
#include "Schedule.h"

void printing(Process fcfs_processes[], Process sjf_processes[], Process srtf_processes[], Process rr_processes[], Process priority_processes[], Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo, int num){

    FILE *file;

    file = fopen("output.txt", "w");

    if (file == NULL) {
        printf("Error opening the file.\n");
    }
    fprintf(file, "FCFS processes\n");
    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", fcfs_processes[i].processId, fcfs_processes[i].turnaroundTime, fcfs_processes[i].waitingTime, fcfs_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for FCFS = %.2f\n", fcfs_algo->turnaround_average);
    fprintf(file, "Average waiting time for FCFS = %.2f\n", fcfs_algo->waiting_average);
    fprintf(file, "Average response time for FCFS = %.2f\n", fcfs_algo->response_average);
    fprintf(file, "\n");
    fprintf(file, "SJF processes\n");
    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", sjf_processes[i].processId, sjf_processes[i].turnaroundTime, sjf_processes[i].waitingTime, sjf_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for SJF = %.2f\n", sjf_algo->turnaround_average);
    fprintf(file, "Average waiting time for SJF = %.2f\n", sjf_algo->waiting_average);
    fprintf(file, "Average response time for SJF = %.2f\n", sjf_algo->response_average);
    fprintf(file, "\n");
    fprintf(file, "SRTF processes\n");
    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", srtf_processes[i].processId, srtf_processes[i].turnaroundTime, srtf_processes[i].waitingTime, srtf_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for SRTF = %.2f\n", srtf_algo->turnaround_average);
    fprintf(file, "Average waiting time for SRTF = %.2f\n", srtf_algo->waiting_average);
    fprintf(file, "Average response time for SRTF = %.2f\n", srtf_algo->response_average);
    fprintf(file, "\n");
    fprintf(file, "RR processes\n");
    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", rr_processes[i].processId, rr_processes[i].turnaroundTime, rr_processes[i].waitingTime, rr_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for RR = %.2f\n", rr_algo->turnaround_average);
    fprintf(file, "Average waiting time for RR = %.2f\n", rr_algo->waiting_average);
    fprintf(file, "Average response time for RR = %.2f\n", rr_algo->response_average);
    fprintf(file, "\n");
    fprintf(file, "Priority processes\n");
    for (int i = 0; i < num; i++)
    {
        fprintf(file, "PID: %d Turnover Time: %d Waiting Time: %d Response Time: %d\n", priority_processes[i].processId, priority_processes[i].turnaroundTime, priority_processes[i].waitingTime, priority_processes[i].responseTime);
    }
    fprintf(file, "Average turnaround time for PRIORITY = %.2f\n", priority_algo->turnaround_average);
    fprintf(file, "Average waiting time for PRIORITY = %.2f\n", priority_algo->waiting_average);
    fprintf(file, "Average response time for PRIORITY = %.2f\n", priority_algo->response_average);
    fprintf(file, "\n");

    checkFastestAlgorithms_file(file, fcfs_algo, sjf_algo, srtf_algo, rr_algo, priority_algo);

    fclose(file);

}


