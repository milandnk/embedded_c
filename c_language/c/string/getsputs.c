#include<stdio.h>
int main(){
    char str[40];
    printf("enter name:");
    // scanf("%s\n",&str);
    // printf("%s\n",str);
    // gets(str);
    fgets(str,40,stdin);
    puts(str);
   
return 0;
}