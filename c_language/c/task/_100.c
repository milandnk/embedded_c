#include <stdio.h>
#include <string.h>
int main()
{
    char str1[50]={0};
    printf("enter string:");
    scanf("%[^\n]s", str1);

    char str2[50]={0};
    printf("enter substring which replace:");
    scanf("%s", str2);

    char str3[50]={0};
    printf("enter replace string:");
    scanf("%s", str3);

    char *ptr = strstr(str1, str2);
    memmove(ptr + strlen(str3), ptr + strlen(str2), strlen(ptr) + strlen(str3) - strlen(str2));
    memmove(ptr, str3, strlen(str3));
    printf("updated string is:%s", str1);
    return 0;
}