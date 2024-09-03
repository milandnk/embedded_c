#include <stdio.h>
int equal(int n, int m, int a[n][m], int b[n][m])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] != b[i][j])
            {
                return 1;
            }
            else
            {
                return 0;

            }
            
            
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
int main()
{
    int n, m;
    printf("enter input n:");
    scanf("%d", &n);
    printf("enter input m:");
    scanf("%d", &m);
    int arr[n][m];
    printf("enter arr 1 inputs :");
    _scan(n, m, arr);
    int brr[n][m];
    printf("enter arr 2 inputs :");
    _scan(n, m, brr);
    printf("arr print\n");
    print_arr(n, m, arr);
    printf("arr print\n");
    print_arr(n, m, brr);
   
    if ( equal(n, m, arr, brr))
    {
        printf("equal");
    }
    else
    {
        printf("not equal");
    }
    
    
    return 0;
}