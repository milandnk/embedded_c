
#include<stdio.h>
void _scan(int n,  int a[n][n])
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
void inter_change_raw(int n,int arr[n][n]){
    for (int i = 0; i < n; i++)
    {
       int temp = arr[i][0];
       arr[i][0] = arr[i][n-1];
       arr[i][n-1] = temp;
        
    }
    
    print_arr(n, arr);
    
    
}
int main(){
    int n,step;
    printf("enter input n:");
    scanf("%d", &n);
    // printf("enter input m:");
    // scanf("%d", &m);
    printf("enter mat 1 inputs :");
    int mat1[n][n];
    _scan(n, mat1);
    printf("your matrix is:\n");
    print_arr(n, mat1);
    inter_change_raw(n,mat1);
return 0;
}