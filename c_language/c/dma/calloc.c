#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    ptr = (int *)calloc(n, sizeof(int)); // Allocate memory for n integers
    
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", ptr[i]);
    }

    free(ptr); // Don't forget to free the allocated memory
    return 0;
}
