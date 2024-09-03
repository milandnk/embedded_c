#include <stdio.h>
#include <math.h>
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
void add_mat(int n, int m, int mat1[n][m])
{
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                printf("%d ", mat1[i][j]);
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    
}
int main()
{
    int n, m;
    printf("enter input n:");
    scanf("%d", &n);
    printf("enter input m:");
    scanf("%d", &m);
    printf("enter mat 1 inputs :");
    int mat1[n][m];
    _scan(n, m, mat1);
    printf("your matrix is:\n");
    print_arr(n, m, mat1);

    printf("your boundry elements matrix is:\n");
    add_mat(n, m, mat1);

    return 0;
}