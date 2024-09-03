#include<stdio.h>
int main(){
    int a=2;
    int *ptr;
    ptr=&a;
    printf("%u\n",ptr);//add of a store in ptr
    printf("%d\n",*ptr);//a using ptr
    printf("%d\n",a);//a value
    printf("%u\n",&a);//add of a
    printf("%u\n",&ptr);//add of ptr
    

return 0;
}