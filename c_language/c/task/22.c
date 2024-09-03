#include <stdio.h>

int main() {
    int i=1,n,fact = 1;
    printf("enter n:");
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        fact = i * fact;
        

    }
    printf("%d\n",fact);

    return 0;
}
