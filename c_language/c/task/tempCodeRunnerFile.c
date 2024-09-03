#include<stdio.h>
#include<math.h>
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
int trace(int n,int a[n][n]){
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + a[i][i];
    }
    return sum;

}
int normal(int n , int a[n][n]){
     int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
             sum = sum + a[i][j] * a[i][j];
        }
        
       
    }
   
    return sqrt(sum);

}
int main(){
    int n, m;
    printf("enter input n:");
    scanf("%d", &n);
    printf("enter arr 1 inputs :");
    int arr[n][n];
    _scan(n, arr);
    printf("your matrix is:\n");
    print_arr(n, arr);
    int tra =  trace(n,arr);
    printf("trace is: %d\n",tra);
    double nor =  normal(n,arr);
    printf("normal is: %f",nor);
return 0;
}