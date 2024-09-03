#include <stdio.h>

int main() {
    int intValue = 10;
    float floatValue = 3.14;
    char charValue = 'A';

    // Declare a void pointer
    void *ptr;

    // Assign the address of intValue to the void pointer
    ptr = &intValue;

    // Dereference and print the value
    printf("Value of intValue: %d\n", *(int*)ptr);

    // Assign the address of floatValue to the void pointer
    ptr = &floatValue;

    // Dereference and print the value
    printf("Value of floatValue: %.2f\n", *(float*)ptr);

    // Assign the address of charValue to the void pointer
    ptr = &charValue;

    // Dereference and print the value
    printf("Value of charValue: %c\n", *(char*)ptr);

    return 0;
}
