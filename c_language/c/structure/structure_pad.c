#include <stdio.h>

// Define a structure with various data types
struct Example {
    char a;     // 1 byte
    int b;      // 4 bytes
    char c;     // 1 byte
};

int main() {
    // Size of the structure
    printf("Size of struct Example: %zu bytes\n", sizeof(struct Example));

    return 0;
}
