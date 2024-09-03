//write a program to change the value of a var. to ten time of its curr. val,write a fun and pass val by ref
#include <stdio.h>

void multiplyByTen(int *x) {
    *x = (*x) * 10;
    printf("%d\n",*x);
}

int main() {
    int num = 5; // Initialize num with a value (e.g., 5)

    printf("Original value of num: %d\n", num);

    multiplyByTen(&num); // Pass the address of num to the function

    printf("Value of num after multiplication: %d\n", num);

    return 0;
}
