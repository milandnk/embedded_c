#include <stdio.h>

// Define a union to represent a value that could be an integer, float, or character
union Value {
    int v1;
    float v2;
    char v3;
};

int main() {
    // Declare a variable of type union Value
    union Value val;

    // Assign values to the members of the union
    val.v1 = 10;
    printf("Integer value: %d\n", val.v1);

    val.v2 = 3.14;
    printf("Float value: %.2f\n", val.v2);

    val.v3 = 'A';
    printf("Character value: %c\n", val.v3);

    // Accessing the members of the union after reassignment
    printf("\n");
    printf("Integer value: %d\n", val.v1); // Accessing intValue after assigning charValue
    printf("Float value: %.2f\n", val.v2); // Accessing floatValue after assigning charValue
    printf("Character value: %c\n", val.v3);

    return 0;
}
