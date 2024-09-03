#include <stdio.h>
#include <string.h>
char *check_pal(int n, char *str, char *str1)
{
    strcpy(str1, str);
    for (int i = 0; i < (n / 2)-1; i++)
    {
        char temp = str1[i];
        str1[i] = str1[n - i - 2];
        str1[n - i - 2] = temp;
    }
    // strcpy(str1, str);
}
int main()
{
    char str[100];
    char str1[100];
    printf("enter a string:");
    scanf("%s", str);
    puts(str);
    int n = strlen(str);
    // char *ptr = str;
    // char *ptr1 = str1;
    check_pal(n + 1, str, str1);
    puts(str1);
    if (strcmp(str,str1)==0)
    {
        printf("string is palindrome");
    }
    else
    {
        printf("not");
    }

    return 0;
}
