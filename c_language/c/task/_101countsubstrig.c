#include <stdio.h>
#include <string.h>
int main()
{
    char str1[50] = {0};
    printf("enter string:");
    scanf("%[^\n]s", str1);

    char str2[50] = {0};
    printf("enter substring which replace:");
    scanf("%s", str2);
    char *ptr = strstr(str1, str2);
    int count = 0;
    while (ptr != NULL)
    {
        count++;
        ptr = strstr(ptr + strlen(str2), str2);
    }

    printf("%d", count);

    return 0;
}