#include<stdio.h>
int main(){
    
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 11; j++) {
           if (j>=7-i && j<=5+i)
           {
            
            printf("*");
           }
           else
           {
            printf(" ");
           }
           
            
        }
        printf("\n");
    }

return 0;
}