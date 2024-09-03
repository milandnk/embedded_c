#include <stdio.h>

int main() {
    char buffer[100];
    int number = 10;
    sprintf(buffer, "The value of number is %d", number);
    printf("Buffer: %s\n", buffer);
    return 0;
}
