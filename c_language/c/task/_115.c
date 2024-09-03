#include<stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    int arr[5]={1,2,3,4,5};
    int *ptr;
    ptr = arr;
    int arr_ptr[5];
    printf("%p\n",ptr);
    for (int i = 0; i < 5; i++,ptr++)
    {
        arr_ptr[i] = (int)ptr;
    }
    for (int i = 0; i < 5; i++)
    {
        printf("array address of %d:%p\n",i+1,arr_ptr[i]);
    }
    
    
return 0;
}