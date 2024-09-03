//rev array
#include<stdio.h>
void print_rev(int *arr,int n){
    int temp,i;
    for(int i =0;i<(n/2);i++ ){
       temp = arr[n-i-1];
        arr[n-i-1] =  arr[i];
         arr[i] = temp;
        
         
    }
}
int main(){
    int arr[7]={1,2,3,4,5,6,7};
   
    print_rev(arr,7);
    for(int i=0;i<7;i++){
        printf("%d th:%d\n",i+1,arr[i]);
    }
    
return 0;
}