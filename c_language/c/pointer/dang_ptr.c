#include<stdio.h>
int *sum(int a,int b){
    int *ptr;
    *ptr = a+b;
    return ptr;
}
int main(){
    int *c;
    c = sum(10,20);
    printf("%d",*c);
return 0;
}