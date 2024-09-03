#include <stdio.h>
#include <string.h>

struct student {
    int roll;
    float cga;
    char name[50]; // Define name as a character array (string)
};

int main() {
    struct student ece[100];
    ece[0].roll = 1600;
    ece[0].cga = 9.2;
    strcpy(ece[0].name, "Milan"); // Use strcpy to copy the name as a string


    printf("Name = %s\n", ece[0].name);
    

    return 0;
}

