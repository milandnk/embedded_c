#include <stdio.h>

int sum(int a, int b);

int main() {
    int a, b;

    printf("Start number: ");
    scanf("%d", &a);

    printf("End number: ");
    scanf("%d", &b);

    int result = sum(a, b);
    printf("Sum of numbers between %d and %d is %d\n", a, b, result);

    return 0;
}

int sum(int a, int b) {
    if (a > b) {
        return 0; 
    } else {
        return a + sum(a + 1, b); 
    }
}
