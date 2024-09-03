#include<stdio.h>
int max(int *arr){
 int max = *arr;
 for (int i = 0; i < 5; i++)
 {
    if (max >= (*arr+i))
    {
        continue;
    }
    else
    {
        max = (*arr+i);
    }
    //printf("%d",max);
    
 }
  printf("%d",max);
 
    
}
int main(){
    int arr[5]={1,5,2,3,4};
    max(arr);
return 0;
}