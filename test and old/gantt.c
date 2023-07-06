#include <stdio.h>
#define MAX_SIZE 100

int main() {
    int gantt[MAX_SIZE] = {4, 4, 4, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 0};
    int size = sizeof(gantt) / sizeof(int);
    int count = 1;
    int previous = gantt[0];
    int time = 0;

    printf("|");

    for (int i = 1; i < MAX_SIZE; i++) {
        if (gantt[i] == 0) {
            break;
        } else if (gantt[i] == previous) {
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

    for (int i = 1; i < MAX_SIZE; i++) {


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

        if (gantt[i] == 0) {
        break;
        }

    }
    time += count;
    for (int j = 0; j < 2*count; j++) {
        printf(" ");
    }

    return 0;
}
