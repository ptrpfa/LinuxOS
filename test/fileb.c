#include "file.h"

int assignB(Processes proccess[], int b, int num){

    for (int i = 0; i<num; i++){
        proccess[i].arrivalTime = b + i;
    }
}