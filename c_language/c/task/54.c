#include <stdio.h>
int main()
{
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            printf("%d raw and %d column element is: %d\n", i + 1, j + 1, arr[i][j]);
        }
    }

    return 0;
}