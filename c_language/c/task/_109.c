#include<stdio.h>
#include<math.h>
int main(){
    int num;
    printf("enter decimal value:");
    scanf("%d",&num);
    double i=0;
    int a;
    double total=0;
    //double total = pow(8,5);
    while (num!= 0)
    {
        
        a = num%8;
        
        total = a*pow(10,i)+total;
        num = num/8;
        
        i++;
        
    }
    
    printf("%.1f",total);


    
return 0;
}