#include <stdio.h>

int main() {
    FILE *fptr; // Declare a pointer to a FILE object
    fptr = fopen("test.txt", "r"); // Open the file in "read" mode

    if (fptr == NULL) {
        printf("File could not be opened.\n");
        return 1; // Return an error code to indicate failure
    }

    char ch;
    fscanf(fptr, "%c", &ch);
    printf("%c\n", ch);

    fclose(fptr); // Close the file when you're done
    return 0;
}
