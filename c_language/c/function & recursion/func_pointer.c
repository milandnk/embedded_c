#include <stdio.h>

// Two example functions that we'll use with function pointers
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    // Declare a function pointer that points to a function taking two integers and returning an integer
    int (*operation)(int, int);

    // Assign the address of the add function to the function pointer
    operation = add;

    // Use the function pointer to call the add function
    int result = operation(10, 5);
    printf("Result of addition: %d\n", result);

    // Reassign the function pointer to point to the subtract function
    operation = subtract;

    // Use the function pointer to call the subtract function
    result = operation(10, 5);
    printf("Result of subtraction: %d\n", result);

    return 0;
}
