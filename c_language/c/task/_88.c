#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
int main(){
    
    char str[6] = "milan";
    int n = strlen(str);
    for (int i = 0; i < n/2; i++)
    {
        char temp = str[i];
        str[i] = str [n-i-1];
        str [n-i-1] = temp;
    }
    puts(str);
    
return 0;
}