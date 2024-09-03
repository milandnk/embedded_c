#include <stdio.h>
void _scan(int n, int m, int a[n][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}
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
void transpose(int n, int m, int a[n][m])
{   int b[m][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            b[j][i] = a[i][j];
        }
    }
    printf("transpose matrix is:\n");
    print_arr(m,n, b);
}
int main()
{
    int n, m;
    printf("enter input n:");
    scanf("%d", &n);
    printf("enter input m:");
    scanf("%d", &m);
    printf("enter arr 1 inputs :");

    int arr[n][m];
    int T_arr[m][n];
    _scan(n, m, arr);
    printf("your matrix is:\n");
    print_arr(n, m, arr);
    transpose(n, m, arr);
    


    return 0;
}