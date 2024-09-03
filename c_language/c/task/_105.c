#include <stdio.h>

int main() {
    char buffer[20] = "1234";
    long n;

    sscanf(buffer, "%ld", &n);
    
    //printf("%ld", n);

    return 0;
}
