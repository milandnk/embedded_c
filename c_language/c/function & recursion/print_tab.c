#include<stdio.h>
void print_tab(int a);
int main(){
    int a;
    printf("enter a");
    scanf("%d",&a);
    print_tab(a);
    
return 0;
}
void print_tab(int a){
    for(int i=1;i<=10;i++){
        printf("%d\t %d\t %d\n",a,i,a*i);
    }
}