#include<stdio.h>
int main(){
    int a,b,c,d,e,f;
    
    printf("Enter the real num of a: ");
    scanf("%d", &c);
    printf("Enter the img num of a: ");
    scanf("%d", &d);
    printf("Enter the real num of b: ");
    scanf("%d", &e);
    printf("Enter the img num of b: ");
    scanf("%d", &f);
    printf("num a is :%d + %d*i\n",c,d);
    printf("num a is :%d + %d*i\n",e,f);
    int sum_real = c+e;
    int sum_img = d+f;
    printf("sum of two complex num a is :%d + %d*i\n",sum_real,sum_img);


return 0;
}