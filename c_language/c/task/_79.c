//left rotate round rotate
#include<stdio.h>
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
void shift(int n,int m,int arr[n][m],int step){
    int brr[n][step];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < step; j++)
        {
            brr[i][j]=arr[i][j];
        }
        
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <m-step; j++)
        {
            arr[i][j]=arr[i][j+step];
        }
        
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <step ; j++)
        {
            arr[i][m-step]=brr[i][j];
        }
    }
    print_arr( n,  m, arr);
    
}
int main(){
    int n, m,step;
    printf("enter input n:");
    scanf("%d", &n);
    printf("enter input m:");
    scanf("%d", &m);
    printf("enter mat 1 inputs :");
    int mat1[n][m];
    _scan(n, m, mat1);
    printf("your matrix is:\n");
    print_arr(n,m, mat1);
    printf("enter left shift step:");
    scanf("%d", &step);
    shift(n, m, mat1,step);
return 0;
}