#include <stdio.h>

int main() {
    int a = 0, b = 1, c, n;

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
        printf("%d ", c);
    }

    printf("\n");

    return 0;
}
