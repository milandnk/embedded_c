#include <stdio.h>
#include <string.h>
int main()
{
    char str[100] = "my name is milan pipaliya";
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        if (str[i]!=' ')
        {
           printf("%c",str[i]);
        }
        else if(str[i]==' '){
            printf("\n");
        }
        
    }

    return 0;
}