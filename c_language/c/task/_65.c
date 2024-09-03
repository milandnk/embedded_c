#include <stdio.h>

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);
    int mergedSize = n + m;

   
    int mergedArray[mergedSize];


    for (int i = 0; i < n; i++) {
        mergedArray[i] = arr1[i];
    }


    for (int i = 0; i < m; i++) {
        mergedArray[n + i] = arr2[i];
    }

   
    printf("Merged Array: ");
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", mergedArray[i]);
    }

    return 0;
}
