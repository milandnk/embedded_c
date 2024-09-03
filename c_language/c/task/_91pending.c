#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{

    char str[100];

    printf("enter a string:");
    fgets(str, 100, stdin);
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            str[i] = str[i] + 32;
        }
    }
    puts(str);

    for (int i = 0; i <= n; i++)
    {
        if (str[i] == ' ')
        {
            memmove(str + i, str + i + 1, n);
        }
        else
        {
            continue;
        }
    }

    puts(str);
    n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (str[i] == str[j])
            {
                for (int k = j; k < n; k++)
                {
                    str[k] = str[k + 1];
                }
                n--;
                j--;
            }
        }
    }
    str[n] = '\0';
    puts(str);
    if ((n-1) == 26)
    {
        printf("it is pangram string");
    }
    else
    {
        printf("it is not pangram string");
    }

    return 0;
}
// Pack my box with five dozen liquor jugs
// The quick brown fox jumps over the lazy dog