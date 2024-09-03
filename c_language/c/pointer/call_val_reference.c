#include<stdio.h>//try to swap value
void call_val(int a,int b);
// void call_ref(int *a,int *b);
int main(){
    int a=4,b=5,next;
    printf("a:%d,b:%d\n",a,b);
     call_val(a,b);
     printf("a:%d,b:%d\n",a,b);
    //    call_ref(&a,&b);
    //   printf("a:%d,b:%d\n",a,b);
   
return 0;
}
void call_val(int a,int b){
    int next =a;
    a=b;
    b=next;
}
// void call_ref(int *a,int *b){
//     int next =*a;
//     *a=*b;
//     *b=next;
// }