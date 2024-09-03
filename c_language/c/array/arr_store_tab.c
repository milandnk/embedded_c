#include <stdio.h>

void generateMultiplicationTable(int num, int table[]) {
    for (int i = 1; i <= 10; i++) {
        table[i - 1] = num * i;
    }
}

int main() {
    int num = 5; // Change this to the number for which you want to generate a table
    int table[10];

    generateMultiplicationTable(num, table);

    printf("Multiplication table for %d:\n", num);
    for (int i = 0; i < 10; i++) {
        printf("%d x %d = %d\n", num, i + 1, table[i]);
    }

    return 0;
}
