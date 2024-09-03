#include<stdio.h>

int main() {
    int num, originalNum, count = 0, rem, result = 0;
    
    printf("Enter the number: ");
    scanf("%d", &num);
    
    originalNum = num;

    while (num != 0) {
        num = num / 10;
        count++;
    }
    printf("your num is %d digit\n",count);
    num = originalNum; 
    
  
    while (num != 0) {
        rem = num % 10;
        result = result + rem * rem * rem;
        num = num / 10;
    }
    
    // Check if the number is Armstrong
    if (result == originalNum) {
        printf("%d is an Armstrong number.\n", originalNum);
    } else {
        printf("%d is not an Armstrong number.\n", originalNum);
    }
    
    return 0;
}
