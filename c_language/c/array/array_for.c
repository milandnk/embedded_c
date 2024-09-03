#include <stdio.h>

int main() {
    int i, n;

    printf("Enter the number of marks: ");
    scanf("%d", &n);

    int mark[n];

    for (i = 0; i < n; i++) {
        printf("Enter mark[%d]: ", i);
        scanf("%d", &mark[i]);
        printf("mark[%d] = %d\n", i, mark[i]);
    }

    return 0;
}
