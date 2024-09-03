#include<stdio.h>
int main(){
    int a[2][5]={{5,2,3,9,1},{1,4,3,9,2}};
    print_arr(2,5,a);
    sort(2,5,a);
return 0;
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
