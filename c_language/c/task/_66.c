#include <stdio.h>

void remove_num(int a[], int *n, int rn) {
    for (int i = 0; i < *n; i++) {
        if (rn == a[i]) {
            for (int j = i; j < *n - 1; j++) { 
                a[j] = a[j + 1];
            }
            (*n)--; 
            i--; 
        }
    }
}

int main() {
    int a[] = {1, 2, 2, 3, 4, 5, 6, 7, 2, 8};
    int n = sizeof(a) / sizeof(a[0]);
    remove_num(a, &n, 2);

    printf("Array after removing all occurrences of 2: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
