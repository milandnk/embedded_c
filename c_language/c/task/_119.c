#include<stdio.h>
int sort(int *arr,int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n -i -1; j++)
        {
            if (arr[j]>arr[j+1])
            {
                int *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            
        }
        
    }
    
    
}
int main(){
    int arr[]={2,54,35,699,1,0,25};
    int n = sizeof(arr)/sizeof(arr[0]);
    sort(arr,n);
     for (int i = 0; i < n; i++)
    {
      printf("%d\t",arr[i]);   
        
    }
   

return 0;
}