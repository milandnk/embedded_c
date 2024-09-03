#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void sort(int n,char str[n]){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (str[j]>str[j+1])
            {
                char temp = str[j];
                str[j] = str[j+1];
                str[j+1] = temp;
                
            }
            
        }
        
    }
    puts(str);
    
}

int main(){
    
    char str[6] = "milan";
    int n = strlen(str);
    puts(str);
    sort(n,str);
    
return 0;
}