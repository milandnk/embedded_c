#include<stdio.h>
int main(){
    int i = 9;
    int *ptr = &i;
    printf("%u\t",ptr);
    ptr++;
    printf("%u\t",ptr);
     ptr--;
    printf("%u\t",ptr);
    ptr+=2;
    printf("%u\t",ptr);
 return 0;
}