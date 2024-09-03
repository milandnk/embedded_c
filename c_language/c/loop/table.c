// #include<stdio.h>
// int main(){
//     int a;
//     scanf("%d",&a);                       using for loop
//     for(int i =1;i<=10;i++){
//         printf("%d %d %d\n",a,i,i*a);
//     }
// return 0;
// }

// #include<stdio.h>
// int main(){
//     int a;
//     scanf("%d",&a);
//     int i =1;                      // using while loop
//     while(i<=10){
//         printf("%d %d %d\n",a,i,i*a);
//         i++;
//     }
// return 0;
// }

#include<stdio.h>
int main(){
    int a;
    scanf("%d",&a);
    int i =1;                      // using do while loop
    do{
        printf("%d %d %d\n",a,i,i*a);
        i++;
    }while(i<=10);
return 0;
}