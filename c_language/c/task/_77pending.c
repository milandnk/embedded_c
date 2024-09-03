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
void mul_mat(int n, int m, int mat1[n][m], int mat2[m][n])
{
   int mat[n][n];
   for (int  i = 0; i < n; i++)
   {
       for (int  j = 0; j < m; j++)
       {
          for (int k = 0; k < m; k++)
          {
            mat[][] = mat[][] +  mat1[][]*mat2[][]
          }
          
          
       }
       
   }
   

    print_arr(n, m, mat);
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
    printf("enter mat 2 inputs :");
    int mat2[m][n];
    _scan(m, n, mat2);
    printf("your matrix is:\n");
    print_arr(m, n, mat2);
    printf("your added matrix is:\n");
    add_mat(n, m, mat1, mat2);

    return 0;
}