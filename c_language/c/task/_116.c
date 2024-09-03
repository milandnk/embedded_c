#include<stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    int arr[2][5]={{1,2,3,4,5},
                    {6,7,8,9,10}};
    int *ptr;
    ptr = arr;
    int arr_ptr[2][5];
    printf("%p\n",ptr);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++,ptr++)
        {
            arr_ptr[i][j] = (int)ptr;
        }
        
       
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
           printf("array address of %d:%d\n",i+j+1,arr_ptr[i][j]);
        }
        
        
    }
    
    
return 0;
}