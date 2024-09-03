#include <stdio.h>
int main()
{
    int age, a;

    if (age <= 5)
    {
        a = 1;
    }
    else if (age > 5 && age < 18)
    {
        a = 2;
    }
    else
    {
        a = 3;
    }

    switch (a)
    {
    case 1:
        printf("child");
        break;
    case 2:
        printf("teenager");
        break;
    default:
        printf("adult");
        break;
    }
    return 0;
}