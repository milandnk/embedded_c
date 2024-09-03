#include <stdio.h>

int main() {
    FILE *fptr; // Declare a pointer to a FILE object
    fptr = fopen("test.txt", "w"); // Open the file in "read" mode

    char ch;
    fprintf(fptr, "%c", "m");
    fprintf(fptr, "%c", "a");
    fprintf(fptr, "%c", "n");
    fprintf(fptr, "%c", "g");
    fprintf(fptr, "%c", "o");

    fclose(fptr); // Close the file when you're done
    fptr = fopen("test.txt", "r"); 
    fscanf(fptr, "%c", &ch);
    printf("%c\n", ch);


    return 0;
}
