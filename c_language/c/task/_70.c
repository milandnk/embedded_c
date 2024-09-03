#include <stdio.h>
void print_arr(int n, int m, int a[n][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void sort(int n, int m, int a[n][m])
{
    for (int i = 0; i < n; i++) // raw
    {
        for (int j = 0; j < m ; j++) // pass
        {
            for (int k = 0; k < m-j-1; k++)
            {
                if (a[i][k] > a[i][k + 1])
                {
                    int temp = a[i][k+1];
                    a[i][k+1] = a[i][k];
                    a[i][k] = temp;
                }
            }
        }
    }
    print_arr(n, m, a);
}

int main()
{
    int n, m;
    printf("enter input n:");
    scanf("%d", &n);
    printf("enter input m:");
    scanf("%d", &m);
    int a[n][m];
    printf("enter inputs :");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d ", &a[i][j]);
        }
        // printf("\n");
    }
    print_arr(n, m, a);
    sort(n, m, a);

    return 0;
}