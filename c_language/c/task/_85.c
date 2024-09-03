#include <stdio.h>
#include <string.h>
void bin(int a,int n, int arr[])
{
    int count=0,i;
    
    for (i = 0; i < 10 && a != 0; i++)
    {   
            arr[i] = a % 2;
            count++;
            a = a / 2;
            
    }

    for (int i = count - 1; i >= 0; i--)
    {
        printf("%d",arr[i]);
    }

    printf("\n");
}
int main()
{
    int a, b, sum;
    int arr[10];
    int n=10;
    printf("enter num 1:");
    scanf("%d", &a);
    printf("enter num 2:");
    scanf("%d", &b);
    sum = a + b;
    bin(a,n, arr);
    bin(b,n, arr);
    bin(sum,n, arr);
    return 0;
}
