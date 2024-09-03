#include <stdio.h>

int main() {
    char c;

    for (int i = 0; i < 6; i++) {
        c = 'A';
        for (int j = 0; j < 11; j++) {
            if (j <= 5 - i || j >= 5 + i) {
                printf("%c", c);
                if (j < 5) {
                    c++;
                } else {
                    c--;
                }
            } else {
                printf(" ");
                if (j == 5)
                    c--;
            }
        }
        printf("\n");
    }
    return 0;
}
