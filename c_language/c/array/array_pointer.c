#include<stdio.h>

// void print_array(int *ptr, int n) {
//     for (int i = 0; i < n; i++, ptr++) {
//         printf("print array %d: %d\n", i, *ptr); // Print array value using pointer
//     }
// }

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("print array %d: %d\n", i, arr[i]); // Print array value using array
    }
}


// void print_array(int arr[], int n) {
//     for (int i = 0; i <= n; i++) {
//         printf("print array %d: %u\n", i, &arr[i]); // Print array value using array address
//     }
// }

// void print_array(int *ptr, int n) {
//     for (int i = 0; i < n; i++,ptr++) {
//         printf("print array %d: %u\n", i, ptr); // Print array value using array address
//     }
// }


int main() {
    int n = 7;
    int arr[7] = {3, 24, 32, 56, 6, 4, 2};
    int *ptr = &arr;
    print_array(arr, n);
    
    return 0;
}
