//decimal to hexadecimal
#include <stdio.h>
#include <math.h>
#include <string.h>
#define a 10
#define b 11
#define c 12
#define d 13
#define e 14
#define f 15

int main()
{
    int n, value,num,l;
    double total = 0, base = 1;
    printf("enter how many digit num:");
    scanf("%d", &n);
    printf("enter decimal num:");
    scanf("%d", &num);
    char hex[n+1];
    int i = 0;
    while (num!=0)
    {  
        l = num%16;
         if(l >= 0 && l <= 9) {
            value = l + '0';
        } else if(l >= 10 && l <= 15) {
            value = l + 'a' - 10;
        }
        hex[i] = value;
        num = num/16;
        i++;
    }
    
    hex[i]='\0';
    n = strlen(hex);
    strrev(hex);
    printf("your decimal num is: %s", hex);

    return 0;
}

// #include <stdio.h>
// #include <math.h>

// int main()
// {
//     int n;
//     printf("enter how many digit num:");
//     scanf("%d", &n);
//     printf("%x", n);

//     return 0;
// }
