#include <stdio.h>

int main() {
    int a = 0, b = 1, c, n, sum = 0;

    printf("Enter the last number in the Fibonacci sequence: ");
    scanf("%d", &n);

    printf("Fibonacci sequence up to %d:\n", n);

    for (int i = 0; i < n; i++) {
        if (i <= 1) {
            c = i;
        } else {
            c = a + b;
            a = b;
            b = c;
        }
        sum = sum + c;
        printf("%d ", c);
    }

    printf("\nSum of Fibonacci numbers up to %d is: %d\n", n, sum);

    return 0;
}
