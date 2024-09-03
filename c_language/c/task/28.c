#include <stdio.h>

void rev(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
    for (int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
}

int main() {
    int n;
    printf("Enter required num: ");
    scanf("%d", &n);
    
    int arr[n]; 
    for (int i = 0; i < n; i++) {
        printf("Enter %d num: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Entered numbers: ");
    for (int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    printf("Reverse order is: ");
    rev(arr, n);
    
    return 0;
}
