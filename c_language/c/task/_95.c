#include<stdio.h>
#include<string.h>
int main(){
    char str[]="milan";
    char str1[]="pipaliya";
    if (strcmp(str,str1)==0)
    {
        printf("both string are equal");
    }
    else if (strcmp(str,str1)>0)
    {
        printf("str is greater");
    }
    else
    {
        printf("str1 is greater");
    } 
return 0;
}