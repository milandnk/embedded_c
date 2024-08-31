#include <stdio.h>

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);

struct Operation {
    int (*ptr)(int, int);
};

int main() {
    
    struct Operation op;

    int a = 10, b = 5;

    op.ptr = &add;
    printf("Add: %d + %d = %d\n", a, b, op.ptr(a, b));

    op.ptr = &subtract;
    printf("Subtract: %d - %d = %d\n", a, b, op.ptr(a, b));

    op.ptr = &multiply;
    printf("Multiply: %d * %d = %d\n", a, b, op.ptr(a, b));

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
