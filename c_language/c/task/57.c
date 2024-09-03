#include<stdio.h>

int main() {
    int b ; 
    int n = 5;
    int arr[5] = {1, 3, 5, 2, 4};

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0 || arr[i] == 1) {
            b = arr[i]; 
            printf("The binary number in the array is: %d\n", b);
            break; 
        }
    }

    

    return 0;
}
