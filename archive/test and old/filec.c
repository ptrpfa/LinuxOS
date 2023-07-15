#include <stdio.h>
#include "file.h"

int main(){

    Processes processA[2];
    Processes processB[2];
    int num = 2;

    assignA(processA,5,num);
    assignB(processB,20,num);

    for (int i = 0; i < num; i++)
    {
        printf("Process A.%d arrival time : %d\n", i + 1,processA[i].arrivalTime);
        printf("Process B.%d arrival time : %d\n", i + 1,processB[i].arrivalTime);
    }
    
    return 0;

}