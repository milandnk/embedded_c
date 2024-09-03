#include<stdio.h>

void slice(char *st, int m, int n) {
    int i;
    for (i = 0; m + i < n; i++) {//run on online compiler
        st[i] = st[m + i];
    }
    st[i] = '\0'; // Null-terminate the sliced substring
}

int main() {
    int m, n;
    char st[100] = "milan";

    slice(st, 2, 4);
    printf("%s", st);

    return 0;
}