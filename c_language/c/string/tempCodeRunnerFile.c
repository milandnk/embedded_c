#include <stdio.h>
#include <string.h>

int main() {
    char name1[6] = "milan";
    char name2[6] = "jay";

    puts(name1);
    puts(name2);

    int result = strcmp(name1, name2);

    if (result < 0) {
        printf("name1 comes before name2\n");
    } else if (result > 0) {
        printf("name2 comes before name1\n");
    } else {
        printf("name1 and name2 are the same\n");
    }

    return 0;
}
