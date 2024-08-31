#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *ptr = NULL;

    // char s[40];
    // ptr = fopen("file.txt","r");

    // fscanf(ptr,"%s",s);
    // puts(s);          //// for reading purpose

    // char s[40] = "how are you";
    // ptr = fopen("file.txt","w");

    // fprintf(ptr,"%s",s);/////for writing 

    char s[40]= "how are you";
    ptr = fopen("file.txt","a");

    fprintf(ptr,"%s",s);
    
}