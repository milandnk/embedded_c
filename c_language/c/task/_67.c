#include<stdio.h>

void common_ele(int arr[], int n) {
    int j;
    for (int i = 0; i < n && i!=j; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                printf("%d ", arr[i]);
                break;
            }
        }
    }
}

int main() {
    int arr[] = {1, 2, 5, 4, 6, 6, 5, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Common numbers are: ");
    common_ele(arr, n);
    
    return 0;
}
