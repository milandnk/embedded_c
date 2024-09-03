#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <stdio_ext.h>

int main()
{
    int n, c, r;
    char str[100] = {0};
    printf("enter a string:");
    // fgets(str, 100, stdin);
    // gets(str);
    scanf("%[^\n]s", str);
    // puts(str);
    n = strlen(str);
    // str[n - 1] = 0;
    //  for (int i = 0; i < 100; i++)
    //      printf("%hhd ", str[i]);
    char change[50];
    printf("enter a change:");
    // fgets(change, 50, stdin);
    scanf(" %[^\n]s", change);
    // gets(change);
    puts(change);
    c = strlen(change);
    // change[c - 1] = 0;
    //  for (int i = 0; i < 50; i++)
    //      printf("%hhd ", change[i]);

    char replace[50] = {0};
    printf("enter a replace:");
    // fgets(replace, 50, stdin);
    scanf(" %[^\n]s", replace);
    r = strlen(replace);

    char *result;
    result = strstr(str, change);
    printf("Substring: %p\n", result);

    if (result != NULL)
    {
        printf("Substring found at position: %ld\n", (result - str));
        char ch[50];
        memmove(ch,result + strlen(change), strlen(result));
        strcpy(result, replace);
        strcat(result,ch);
        printf("%s\n",ch);
        printf("Substring result: %s\n", result);
        printf("Substring: %s\n", str);
    }
    else
    {
        printf("Substring not found\n");
    }
    return 0;
}
// my name is milan