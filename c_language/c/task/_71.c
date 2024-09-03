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
    for (int i = 0; i < n; i++) // col
    {
        for (int j = 0; j < m ; j++) // pass
        {
            for (int k = 0; k < m-j-1; k++)
            {
                if (a[k][i] > a[k + 1][i])
                {
                    int temp = a[k+1][i];
                    a[k+1][i] = a[k][i];
                    a[k][i] = temp;
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
            scanf("%d", &a[i][j]);
        }
        // printf("\n");
    }
    print_arr(n, m, a);
    sort(n, m, a);

    return 0;
}