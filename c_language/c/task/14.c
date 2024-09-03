#include <stdio.h>
#include <math.h>

int main() {
    float p, r, t, a;

    printf("Enter principal amount: ");
    scanf("%f", &p);

    printf("Enter annual interest rate (in percentage): ");
    scanf("%f", &r);

    printf("Enter time in years: ");
    scanf("%f", &t);;

    a = p * pow((1 + r/100), t);

    printf("Compound interest after %.2f years: %.2f\n", t, a);

    return 0;
}
