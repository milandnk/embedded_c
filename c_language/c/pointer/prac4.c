#include<stdio.h>

void sum_avg(int a, int b, int *sum, float *avg) {
    *sum = a + b;
    *avg = (float)(*sum) / 2;
}

int main() {
    int a, b, sum;
    float avg;
    a = 3;
    b = 5;
    sum_avg(a, b, &sum, &avg);
    printf("%d\n", sum);
    printf("%f\n", avg);

    return 0;
}
