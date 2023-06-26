#include <stdio.h>

int main() {
    // Define the headers
    char headers[4][20] = {
        "Header 1",
        "Header 2",
        "Header 3",
        "Header 4"
    };

    // Define the table data
    int tableData[7][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
        {17, 18, 19, 20},
        {21, 22, 23, 24},
        {25, 26, 27, 28}
    };

    // Print the top border
    printf("%c", 201); // Top-left corner
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", 205); // Horizontal line
        }
        if (i != 3) {
            printf("%c", 203); // Intersection
        }
    }
    printf("%c\n", 187); // Top-right corner

    // Print the headers
    printf("%c", 186); // Vertical line
    for (int i = 0; i < 4; i++) {
        printf("%-20s%c", headers[i], 186); // Header and vertical line
    }
    printf("\n");

    // Print the header-row separator
    printf("%c", 204); // Left T-intersection
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", 205); // Horizontal line
        }
        if (i != 3) {
            printf("%c", 206); // T-intersection
        }
    }
    printf("%c\n", 185); // Right T-intersection

    // Print the table data
    for (int i = 0; i < 7; i++) {
        printf("%c", 186); // Vertical line
        for (int j = 0; j < 4; j++) {
            printf("%-20d%c", tableData[i][j], 186); // Data and vertical line
        }
        printf("\n");

        if (i != 6) {
            printf("%c", 204); // Left T-intersection
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 20; k++) {
                    printf("%c", 205); // Horizontal line
                }
                if (j != 3) {
                    printf("%c", 206); // T-intersection
                }
            }
            printf("%c\n", 185); // Right T-intersection
        }
    }

    // Print the bottom border
    printf("%c", 200); // Bottom-left corner
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", 205); // Horizontal line
        }
        if (i != 3) {
            printf("%c", 202); // Intersection
        }
    }
    printf("%c\n", 188); // Bottom-right corner

    return 0;
}