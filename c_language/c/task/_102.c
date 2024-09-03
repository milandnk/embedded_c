#include<stdio.h>
#define true = 1;
#define false = 0;

int main(){
    printf("enter input in bool like 1 or 0:");
    int n=1;
    scanf("%d",&n);
     if (n==1)
    {
       printf("true");
    }
    else if (n==0)
    {
        
        printf("false");
    }
    else
    {
       printf("not valid");
    }
    
return 0;
}