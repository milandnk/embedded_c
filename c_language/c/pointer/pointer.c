#include<stdio.h>
int main(){
    int age = 18;
    scanf("%d",&age);
    int *ptr = &age;
    printf("%u\n",&age);
    printf("%d\n",ptr);
    printf("%d\n",*ptr);
    printf("%u\n",&ptr);
return 0;
}