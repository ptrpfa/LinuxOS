#include <stdio.h>
#include <string.h>
#include "Schedule.h"

void checkFastestAlgorithms(Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo){
    // Check fastest average turnaround time
    float fastest_turnaround = fcfs_algo->turnaround_average;
    char fastest_turnaround_algo[20] = "FCFS";

    if (sjf_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = sjf_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "SJF");
    }

    if (srtf_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = srtf_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "SRTF");
    }

    if (rr_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = rr_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "RR");
    }

    if (priority_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = priority_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "Priority");
    }

    printf("Algorithm with fastest average turnaround time: %s\n", fastest_turnaround_algo);
    printf("Fastest average turnaround time: %.2f\n", fastest_turnaround);
    printf("\n");

    // Check fastest average waiting time
    float fastest_waiting = fcfs_algo->waiting_average;
    char fastest_waiting_algo[20] = "FCFS";

    if (sjf_algo->waiting_average < fastest_waiting) {
        fastest_waiting = sjf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SJF");
    }

    if (srtf_algo->waiting_average < fastest_waiting) {
        fastest_waiting = srtf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SRTF");
    }

    if (rr_algo->waiting_average < fastest_waiting) {
        fastest_waiting = rr_algo->waiting_average;
        strcpy(fastest_waiting_algo, "RR");
    }

    if (priority_algo->waiting_average < fastest_waiting) {
        fastest_waiting = priority_algo->waiting_average;
        strcpy(fastest_waiting_algo, "Priority");
    }

    printf("Algorithm with fastest average waiting time: %s\n", fastest_waiting_algo);
    printf("Fastest average waiting time: %.2f\n", fastest_waiting);
    printf("\n");

    // Check fastest average response time
    float fastest_response = fcfs_algo->response_average;
    char fastest_response_algo[20] = "FCFS";

    if (sjf_algo->response_average < fastest_response) {
        fastest_response = sjf_algo->response_average;
        strcpy(fastest_response_algo, "SJF");
    }

    if (srtf_algo->response_average < fastest_response) {
        fastest_response = srtf_algo->response_average;
        strcpy(fastest_response_algo, "SRTF");
    }

    if (rr_algo->response_average < fastest_response) {
        fastest_response = rr_algo->response_average;
        strcpy(fastest_response_algo, "RR");
    }

    if (priority_algo->response_average < fastest_response) {
        fastest_response = priority_algo->response_average;
        strcpy(fastest_response_algo, "Priority");
    }

    printf("Algorithm with fastest average response time: %s\n", fastest_response_algo);
    printf("Fastest average response time: %.2f\n", fastest_response);
    printf("\n");
}

void checkFastestAlgorithms_file(FILE *file, Algo *fcfs_algo, Algo *sjf_algo, Algo *srtf_algo, Algo *rr_algo, Algo *priority_algo){
    // Check fastest average turnaround time
    float fastest_turnaround = fcfs_algo->turnaround_average;
    char fastest_turnaround_algo[20] = "FCFS";

    if (sjf_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = sjf_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "SJF");
    }

    if (srtf_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = srtf_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "SRTF");
    }

    if (rr_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = rr_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "RR");
    }

    if (priority_algo->turnaround_average < fastest_turnaround) {
        fastest_turnaround = priority_algo->turnaround_average;
        strcpy(fastest_turnaround_algo, "Priority");
    }

    fprintf(file,"Algorithm with fastest average turnaround time: %s\n", fastest_turnaround_algo);
    fprintf(file,"Fastest average turnaround time: %.2f\n", fastest_turnaround);
    fprintf(file,"\n");

    // Check fastest average waiting time
    float fastest_waiting = fcfs_algo->waiting_average;
    char fastest_waiting_algo[20] = "FCFS";

    if (sjf_algo->waiting_average < fastest_waiting) {
        fastest_waiting = sjf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SJF");
    }

    if (srtf_algo->waiting_average < fastest_waiting) {
        fastest_waiting = srtf_algo->waiting_average;
        strcpy(fastest_waiting_algo, "SRTF");
    }

    if (rr_algo->waiting_average < fastest_waiting) {
        fastest_waiting = rr_algo->waiting_average;
        strcpy(fastest_waiting_algo, "RR");
    }

    if (priority_algo->waiting_average < fastest_waiting) {
        fastest_waiting = priority_algo->waiting_average;
        strcpy(fastest_waiting_algo, "Priority");
    }

    fprintf(file,"Algorithm with fastest average waiting time: %s\n", fastest_waiting_algo);
    fprintf(file,"Fastest average waiting time: %.2f\n", fastest_waiting);
    fprintf(file,"\n");

    // Check fastest average response time
    float fastest_response = fcfs_algo->response_average;
    char fastest_response_algo[20] = "FCFS";

    if (sjf_algo->response_average < fastest_response) {
        fastest_response = sjf_algo->response_average;
        strcpy(fastest_response_algo, "SJF");
    }

    if (srtf_algo->response_average < fastest_response) {
        fastest_response = srtf_algo->response_average;
        strcpy(fastest_response_algo, "SRTF");
    }

    if (rr_algo->response_average < fastest_response) {
        fastest_response = rr_algo->response_average;
        strcpy(fastest_response_algo, "RR");
    }

    if (priority_algo->response_average < fastest_response) {
        fastest_response = priority_algo->response_average;
        strcpy(fastest_response_algo, "Priority");
    }

    fprintf(file,"Algorithm with fastest average response time: %s\n", fastest_response_algo);
    fprintf(file,"Fastest average response time: %.2f\n", fastest_response);
    fprintf(file,"\n");
}