#include<stdio.h>

int main() {
    int row;
    int n=5;

    // Pattern 1: Ascending sequence
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    // Pattern 2: Descending sequence
    for (int i = (n-1); i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    return 0;
}
