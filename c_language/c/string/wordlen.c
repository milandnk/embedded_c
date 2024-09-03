#include <stdio.h>
#include<string.h>

int count(const char arr[]) {
    int count = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        count++;
    }
    return count;
}

int main() {
    char name[100];
    gets(name);
    printf("length is: %d", count(name));
    
    return 0;
}
