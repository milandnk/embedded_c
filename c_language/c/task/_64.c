#include<stdio.h>

void print_arr(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n"); 
}

void remove_duplicates(int a[], int *n){
    for (int i = 0; i < (*n); i++)
    {
        int j = i+1;
        while ( j < (*n))
        {
            if (a[i] == a[j])
            {
                for (int k = j; k < (*n)-1 ; k++)
                {
                    a[k] = a[k+1];
                }
                (*n)--; 
                j--; 
            }
          j++;
            
        }
    }
}

int main(){
    int a[] = {1, 5, 5, 5, 8, 7, 9, 5,6,11,5,31,52,65,22,14,22,22,77,96};
    int n = sizeof(a) / sizeof(a[0]);
    
    printf("Array before removing duplicates: ");
    print_arr(a, n);

    remove_duplicates(a, &n);

    printf("Array after removing duplicates: ");
    print_arr(a, n);

    return 0;
}
