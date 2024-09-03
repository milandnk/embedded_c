#include <stdio.h>
#include <string.h>
int main(){
    char str[] = "milan pipaliya rameshbhai";
    int n = strlen(str);
    printf("%c ", str[0]);
    for (int i = 0; i <= n; i++){
        if (str[i] == ' '){
            printf("%c ", str[i + 1]);
        }
    }
    return 0;
}