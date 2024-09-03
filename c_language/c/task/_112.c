#include <stdio.h>
#include <math.h>
int main()
{
    int num, value;
    printf("enter decimal value:");
    scanf("%d", &num);
    double i = 0;
    int a;
    double total = 0;
    // double total = pow(8,5);
    while (num != 0)
    {
        if (hex[j] >= '0' && hex[j] <= '9')
        {
            value = hex[j] - '0';
        }
        else if (hex[j] >= 'a' && hex[j] <= 'f')
        {
            value = hex[j] - 'a' + 10;
        }

        a = num % 2;

        total = a * pow(10, i) + total;
        num = num / 2;

        i++;
    }

    printf("%.1f", total);

    return 0;
}