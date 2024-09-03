#include<stdio.h>
int main(){
    int arr[10]={2,0,1,3,0,5,0,6,4,7};
    int *ptr =arr;
    printf("%d\n",*ptr);
    ptr=ptr+2;
    printf("%d\n",*ptr);
return 0;
}