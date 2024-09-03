#include<stdio.h>

float calculateAverage(int arr[5]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum = sum + arr[i];
    }
    return (float)sum / 5; 
}

int main() {
    int n = 5;
    int arr[5] = {1, 2, 3, 4, 5};
     
    float avg = calculateAverage(arr);
    printf("Average is: %.2f\n", avg); 

    return 0;
}
