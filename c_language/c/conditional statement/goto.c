#include <stdio.h>

int main() {
    int i = 0;
 label:

        printf("%d ", i);
        goto label; 
  

        printf("\nFinished\n");

    return 0;
}
