#include <stdio.h>
int main()
{
    int marks, a;
    printf("enter marks:");
    scanf("%d", &marks);
    if (marks >= 33 && marks <= 100)
    {
        printf("pass");
    }
    else
    {
        printf("fail");
    }

    return 0;
}