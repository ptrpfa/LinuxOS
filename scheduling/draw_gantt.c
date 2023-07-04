#include <stdio.h>
#include "schedule.h"

void draw_gantt(int gantt[], int size) {
    int count = 1;
    int previous = gantt[0];
    int time = 0;

    printf("|");

    for (int i = 1; i < size; i++) {

        if (gantt[i] == previous) {
            count++;
        } else {
            for (int j = 0; j < count; j++) {
                printf("-");
            }
            printf("%d", previous);
            for (int j = 0; j < count; j++) {
                printf("-");
            }
            printf("|");
            time += count;
            count = 1;
        }
        previous = gantt[i];
    }

    for (int j = 0; j < count; j++) {
        printf("-");
    }
    printf("%d", previous);
    for (int j = 0; j < count; j++) {
        printf("-");
    }
    printf("|");
    printf("\n");

    printf("0");
    count = 1;
    time = 0;
    previous = gantt[0];

    for (int i = 1; i < size+1; i++) {
        if (gantt[i] == previous) {
            count++;
        } else {
            time += count;
            if (time >= 10)
            {
                for (int j = 0; j < 2*count; j++) {
                printf(" ");
                }
                printf("%d", time);
                count = 1;
            }
            else{
                for (int j = 0; j < 2*count + 1; j++) {
                printf(" ");
                }
                printf("%d", time);
                count = 1;
            }
            
        }
        previous = gantt[i];
    }
    time += count;
    for (int j = 0; j < 2*count; j++) {
        printf(" ");
    }

}
