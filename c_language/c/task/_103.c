#include <stdio.h>

int main() {
    float floatValue = 3.14;
    char buffer[20]; 

    sprintf(buffer, "%f", floatValue);

    printf("Float value as string: %s\n", buffer);

    return 0;
}
