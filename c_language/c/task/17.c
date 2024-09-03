#include <stdio.h>

int Vowel(char ch) {
     
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
        return 1; 
    } else {
        return 0; 
    }
}

int main() {
    char ch;

    printf("Enter a character: ");
    scanf(" %c", &ch);
   
    if (Vowel(ch)) {
        printf("%c is a vowel.\n", ch);
    } else {
        printf("%c is not a vowel.\n", ch);
    }

    return 0;
}

