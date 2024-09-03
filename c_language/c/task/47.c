#include <stdio.h>

int main() {
    int i, j, k;

    // Printing upper half of the pattern
    for (i = 1; i <= 5; i++) {
        k = 1;
        for (j = 1; j <= 9; j++) {
            if (j >= 6 - i && j <= 4 + i) {
                printf("%d", k);
                if (j < 5) {
                    k++;
                } else {
                    k--;
                }
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    
    for (i = 4; i >= 1; i--) {
        k = 1;
        for (j = 1; j <= 9; j++) {
            if (j >= 6 - i && j <= 4 + i) {
                printf("%d", k);
                if (j < 5) {
                    k++;
                } else {
                    k--;
                }
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
