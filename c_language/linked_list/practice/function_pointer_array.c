#include <stdio.h>

// Function declarations
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);

int main() {
    int (*operations[3])(int, int) = {add, subtract, multiply};

    int a = 5, b = 3;

    int result1 = operations[0](a, b);
    int result2 = operations[1](a, b);
    int result3 = operations[2](a, b);

    // Print the results
    printf("Add: %d + %d = %d\n", a, b, result1);
    printf("Subtract: %d - %d = %d\n", a, b, result2);
    printf("Multiply: %d * %d = %d\n", a, b, result3);

    return 0;
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}
