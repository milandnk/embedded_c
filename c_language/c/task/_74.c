#include<stdio.h>
void _scan(int n, int a[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}
void print_arr(int n, int a[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
void det(int n, int a[n][n])
{
    int i,j,k;
    i = a[0][0]*((a[1][1]*a[2][2])-(a[1][2]*a[2][1]));
    j = a[0][1]*((a[1][0]*a[2][2])-(a[1][2]*a[2][0]));
    k = a[0][2]*((a[1][0]*a[2][1])-(a[1][1]*a[2][0]));
    int det = i - j + k;
    printf("determinate of given matrix is:%d\n",det);
}
int main(){
    int n=3;
    printf("enter input of 3 x 3 matrix inputs :");
    int arr[n][n];
    _scan(n, arr);
    printf("your matrix is:\n");
    print_arr(n, arr);
    det(n, arr);

return 0;
}