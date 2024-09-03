#include<stdio.h>
int main(){
    int raw;
    printf("enter raw:");
    scanf("%d\n",&raw);
    for (int i=1;i<=raw;i++){
        for(int j=1;j<=i;j++){
            printf("* ");
        }
        printf("\n");
    }
return 0;
}