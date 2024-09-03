#include <stdio.h>

// Define a structure for storing an address
struct Address {
    char street[50];
    char city[50];
    char state[20];
    int zipCode;
};

// Define a structure for storing a person
struct Person {
    char name[50];
    int age;
    struct Address a; // Nested structure
};

int main() {
    // Declare a variable of type Person
    struct Person p;

    // Assign values to the nested structures
    strcpy(p.name, "milan");
    p.age = 20;
    strcpy(p.a.street, "123 Main St");
    strcpy(p.a.city, "surat");
    strcpy(p.a.state, "gujarat");
    p.a.zipCode = 12345;

    // Print the details of the person
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Address: %s, %s, %s, %d\n", p.a.street, p.a.city, p.a.state, p.a.zipCode);

    return 0;
}
