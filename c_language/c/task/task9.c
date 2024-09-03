#include<stdio.h>
int main(){
    int a,b,temp;
    printf("Enter the a: ");
    scanf("%d", &a);
    
    printf("Enter the b: ");
    scanf("%d", &b);

    temp =b;
    b=a;
    a=temp;

     printf("swap\n");
    printf("Enter the a: %d",a);
     printf("\n");
    printf("Enter the b : %d",b);
   


return 0;
}