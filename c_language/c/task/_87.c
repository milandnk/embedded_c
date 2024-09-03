#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
int main(){
        int n = 8;
    char str[9] = "abcdcba";

    char str1[9];
    printf("%s", str);
    strcpy(str1, str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str1[i];
        str1[i] = str1[n - i - 1];
        str1[n - i - 1] = temp;
    }
    puts(str1);
    if (strcmp(str,str1)==1)
    {
        printf("it is palindrome");
    }
    else
    {
        printf("not palindrome");
    }
    
    
return 0;
}