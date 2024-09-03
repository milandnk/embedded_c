#include <stdio.h>

int main() {
    int i=1,n,sum = 0;
    printf("enter n:");
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        sum = i + sum;
        

    }
    printf("%d\n",sum);

    return 0;
}

