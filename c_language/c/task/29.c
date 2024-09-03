#include <stdio.h>
int main() {
    int num, originalNum, rem, result = 0;
    
    printf("Enter the number: ");
    scanf("%d", &num);
    
    originalNum = num;

    while (num != 0) {
        rem = num % 10;
        result = result * 10 + rem;
        num = num / 10;
    }

    if (originalNum == result) {
        printf("The number is a palindrome.\n");
    } else {
        printf("The number is not a palindrome.\n");
    }
    
    return 0;
}

