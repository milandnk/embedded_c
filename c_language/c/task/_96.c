#include <stdio.h>
#include <string.h>
int main()
{
    char str[30];
    printf("enter string one:");
    gets(str);
    for (int i = 0; i < 30; i++)
    {
        str[i] = toupper(str[i]);
    }
    
    
    char str1[30];
    printf("enter string two:");
    gets(str1);
    for (int i = 0; i < 30; i++)
    {
        str1[i] = toupper(str1[i]);
    }
    // for (char ch = 'A',ch1 = 'a'; ch <= 'Z',ch1 <='z';ch1++, ch++)
    // {
    //     ch1 = ch;
    // }
    if (strcmp(str, str1) == 0)
    {
        printf("both string are equal");
    }
    else
    {
        printf("not equal");
    }
    return 0;
}