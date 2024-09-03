#include<stdio.h>
int main(){
    int age =18;
    int *ptr=&age;
    int **pptr=&ptr;
    printf("%d\n",age);
    printf("%u\n",&age);
    printf("%u\n",ptr);
    printf("%d\n",*ptr);
    printf("%d\n",*(&ptr));
    printf("%d\n",**pptr);
    printf("%u\n",pptr);

return 0;
}