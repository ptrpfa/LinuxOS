#include "file.h"

int assignA(Processes proccess[], int a, int num){

    for (int i = 0; i<num; i++){
        proccess[i].arrivalTime = a + i;
    }
}