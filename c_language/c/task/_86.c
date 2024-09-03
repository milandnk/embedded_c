#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "milaan pipaliya";
    int n = strlen(str);
    
     for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (str[i] == str[j]) {
                    for (int k = j; k < n; k++) {
                        str[k] = str[k + 1];
                    }
                    n--; 
                    j--; 
            }
        }
    
     }
    str[n] = '\0';
    puts(str);
    
    return 0;
}
