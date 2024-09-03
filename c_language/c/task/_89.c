#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void rev(int n,char str[n],int a,int i){
    
  
    char temp = str[i];
    str[i] = str [n-i-1];
    str [n-i-1] = temp;
    if (a!=0)
    {
        a--;
        i++;
        rev(n,str, a,i);
    }
    else
    {
        puts(str);
    }
    
    
} 
int main(){
    
    char str[6] = "milan";
    int n = strlen(str);
    int a = n/2;
    int i=0;
    
    puts(str);
    rev(n,str, a,i);
    
return 0;
}