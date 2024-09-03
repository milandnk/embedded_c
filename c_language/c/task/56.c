#include<stdio.h>

int main() {
    int max,min, n = 5;
    int arr[5] = {1, 3, 5, 2, 4};

    max = arr[0]; 

    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i]; 
        }
    }

    printf("The maximum number in the array is: %d\n", max);

    min = arr[0]; 

    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            max = arr[i]; 
        }
    }

    printf("The minimum number in the array is: %d\n", min);

    return 0;
}
