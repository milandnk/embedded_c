#include <stdio.h>
#include <string.h>

struct student {
    int roll;
    float cga;
    char name[50];
};

void printInfo(struct student *s1) {
    printf("Roll: %d\n", s1->roll);
    printf("CGA: %f\n", s1->cga);
    printf("Name: %s\n", s1->name);

    s1->roll = 500; // Modify the roll value through the pointer
}

int main() {
    struct student s[5];

    // Initialize student data for s[0]
    s[0].roll = 1600;
    s[0].cga = 9.2;
    strcpy(s[0].name, "Milan");

    // Call printInfo function by passing a pointer
    printInfo(&s[0]);

    // Check if the roll value has changed
    printf("Updated Roll: %d\n", s[0].roll);

    return 0;
}
