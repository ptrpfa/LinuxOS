#include <stdio.h>
#include <limits.h>

int main(){

    int choice;

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
        }

        switch(choice) {
            case 1:
                printf("You chose FCFS\n");
                // Add code for FCFS scheduling algorithm here
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