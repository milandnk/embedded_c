#include<stdio.h>
int add(int a){
    printf("enter address of a:%u\n",&a);//we send only value dont send address so address are dif
}
int main(){
    int i=4;
    printf("enter add of i:%u\n",&i);//i add
    add(i);//a add
    printf("enter add of i:%u\n",&i);//i add

    
return 0;
}