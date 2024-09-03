#include<stdio.h>

int main() {
    int num, sum = 0, sq;
    printf("Enter the number: ");
    scanf("%d", &num);
    
    sq = num * num;

    while (sq != 0) {
        sum = sum + sq % 10;
        sq = sq / 10;
    }

    if (sum == num) {
        printf("%d is a neon number.\n", num);
    } else {
        printf("%d is not a neon number.\n", num);
    }
     
    return 0;
}
