#include<stdio.h>
void print_hello(int n);
int main(){
    int n;
    printf("enter count");
    scanf("%d",&n);
    print_hello(n);

    
return 0;
}
void print_hello(int n){
   if (n==0){return;}
   else{
    printf("hello\n");
    n--;
    print_hello(n--);
   }
}