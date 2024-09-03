#include <stdio.h>
#include <string.h>

int main() {
    char word;
    char name[101]; 

    printf("Enter a line of text: ");
    
    int i = 0;
    while (1) {
        scanf("%c", word);
        if (word == '\n') {
            break; // Exit the loop when Enter is pressed
        }
        name[i] = word;
        i++;
    }
    
    name[i] = '\0'; // Null-terminate the string

   puts(name);

    return 0;
}
