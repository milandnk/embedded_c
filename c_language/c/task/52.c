#include <stdio.h>
int main()
{
    int i, j,n;
    printf("enter value odd n:");
    scanf("%d",&n);

    for (i = 1; i <= (n+1)/2; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (j <= (n+3)/2  - i || j >= (n-1)/2 + i)
            {

                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (i = (n-1)/2; i >= 1; i--)
    {
        for (j = 1; j <= n; j++)
        {
            if (j <= (n+3)/2  - i || j >= (n-1)/2 + i)
            {

                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}