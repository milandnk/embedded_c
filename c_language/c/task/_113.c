#include <stdio.h>
#include <math.h>
int main(){
    
    int num;
    printf("enter binary value:");
    scanf("%d", &num);
    double i = 0;
    double a, total = 0;
    // double total = pow(8,5);
    while (num!= 0)
    {
        a = num % 10;
        total = a * pow(2, i) + total;
        num = num / 10;
        i++;
    }
    printf("%f", total);

    return 0;
}