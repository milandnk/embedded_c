#include <stdio.h>

int main() {
    char data[] = "The value of number is 10";
    int number;
    sscanf(data, "The value of number is %d", &number);
    printf("Number: %d\n", number);
    return 0;
}
