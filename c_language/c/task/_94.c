#include <stdio.h>
#include <string.h>

int main() {
    int n = 8;
    int arr[n];

    printf("Enter numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int z = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            z++;
        } else {
            break;
        }
    }

    printf("Recreated array: ");
    for (int i = z; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
