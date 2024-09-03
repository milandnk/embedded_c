#include <stdio.h>

int main() {
    int start, end, num, originalNum, rem, result;
    
    printf("Enter the starting number: ");
    scanf("%d", &start);
    
    printf("Enter the ending number: ");
    scanf("%d", &end);
    
    printf("Armstrong numbers between %d and %d are:\n", start, end);
    
    for (num = start; num <= end; ++num) {
        originalNum = num;
        result = 0;
        
        while (originalNum != 0) {
            rem = originalNum % 10;
            result = result+ rem * rem * rem;
            originalNum = originalNum/ 10;
        }
        
       
        if (num == result) {
            printf("%d\n", num);
        }
    }
    
    return 0;
}
