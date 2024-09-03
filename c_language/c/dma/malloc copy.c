#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    ptr = (int *)malloc(5 * sizeof(int));
    
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    ptr[0] = 1;
    ptr[1] = 3;
    ptr[2] = 5;
    ptr[3] = 7;
    ptr[4] = 9;

    for (int i = 0; i < 5; i++) {
        printf("%d\t", ptr[i]);
    }

    free(ptr); // Free the allocated memory

    ptr = (int *)realloc(ptr, 3 * sizeof(int)); // Reallocate memory for 3 integers

    if (ptr == NULL) {
        printf("Memory reallocation failed.\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        printf("%d\t", ptr[i]);
    }

    free(ptr); // Free the reallocated memory
    return 0;
}

