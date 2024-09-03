#include <stdio.h>
#include <math.h>
#include<string.h>
#define a 10
#define b 11
#define c 12
#define d 13
#define e 14
#define f 15

int main()
{
    int n, value;
    double total = 0,base=1;
    printf("enter how many digit num:");
    scanf("%d", &n);
   
    char hex[n + 1];
    scanf("%s", hex);
    printf("your hexadecimal num is:%s\n", hex);
    n = strlen(hex);
    int i = 0;
    while (i < n)
    {
        for(int j = n - 1; j >= 0; j--) {
        if(hex[j] >= '0' && hex[j] <= '9') {
            value = hex[j] - '0';
        } else if(hex[j] >= 'a' && hex[j] <= 'f') {
            value = hex[j] - 'a' + 10;
        }
        
        //total = total + value * (pow(16, i));
        total+=hex[i]*base;
        base = base*16;
        i++;
    }
    }
    printf("your decimal num is: %.2f", total);

    return 0;
}


















// #include <stdio.h>
// #include <math.h>


// int main()
// {
//     int n;
//     printf("enter how many digit num:");
//     scanf("%x", &n);
//     printf("%d", n);

//     return 0;
// }
