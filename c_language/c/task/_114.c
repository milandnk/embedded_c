#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* sum(int n){
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    printf("sum is:%d\n", sum);
    // printf("%u\n", &sum);
    int *ptr = &sum;
    printf("%u\n", ptr);
    return ptr;
}
int main()
{
    int n, *add;
    printf("enter a n:");
    scanf("%d", &n);
    add=sum(n);
    printf("%d", add);
    return 0;
}