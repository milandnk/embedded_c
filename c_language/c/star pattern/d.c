#include<stdio.h>
int main(){
    int raw;
    // printf("enter raw:");
    // scanf("%d\n",&raw);
    for (int i=1;i<=5;i++){
        for(int j=1;j<=i;j++){
            printf("%d ",j);
        }
        printf("\n");
    }
return 0;
}