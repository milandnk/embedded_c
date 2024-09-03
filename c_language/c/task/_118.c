#include <stdio.h>
int main()
{
    int a = 3, b = 4;
    int *c = &a;
    int *d = &b;
    //swap(c, d);
    printf("%d", a);
    printf("%d\n", b);
    int *temp = *c;
    *c = *d;
    *d = temp;
    printf("%d", a);
    printf("%d", b);
    return 0;
}