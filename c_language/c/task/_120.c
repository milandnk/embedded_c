#include <stdio.h>

int sort( int n, int m,char (*arr)[m])
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m - i - 1; j++)
            {
                if (arr[k][j] > arr[k][j + 1])
                {
                    int temp = arr[k][j];
                    arr[k][j] = arr[k][j + 1];
                    arr[k][j + 1] = temp;
                }
            }
        }
    }
}

int main()
{
    char arr[3][7] = {"apple",
                      "orange",
                      "banana"};

    sort( 3, 7, arr);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
           printf("%c",arr[i][j]);
        }
        printf("\n");
        
    }
    

    return 0;
}