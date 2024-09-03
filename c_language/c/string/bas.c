#include <stdio.h>

int main() {
    char str[6] = "milan";
    char *ptr = &str;
    int i;
    for (i = 0; i < 5; i++) {
        printf("%u\n", &ptr[i]); // Use %c to  address print individual characters
    }
    for (i = 0; i < 5; i++) {
        printf("%c\n", ptr[i]); // Use %c to print individual characters
    }
    printf("%s\n", ptr); //use for full word


    return 0;
}
