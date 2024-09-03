#include <stdio.h>

void ascending(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < (n - 1); i++)
    {
        for (j = 0; j < (n - i - 1); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void descending(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < (n - 1); i++)
    {
        for (j = 0; j <( n - i - 1); j++)
        {
            if (arr[j] < arr[j + 1])
            {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int order, n;
    int arr[10];
    printf("Enter array values 10: ");
     printf("Enter 1 for ascending and 2 for descending: \n");
    for (int k = 0; k < 10; k++)
    {
        scanf("%d\t", &arr[k]);
    }
    
    printf("Enter 1 for ascending and 2 for descending: \n");
        scanf("%d\n", &order);
   
    
    n = 10; // Size of the array

   
    switch (order)
    {
    case 1:
        ascending(arr, n);
        printf("Ascending order:\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d\t", arr[i]);
        }
        printf("\n");

        break;
    case 2:
        descending(arr, n);
        printf("Descending order:\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d\t", arr[i]);
        }
        printf("\n");

        break;
    default:
        printf("Invalid choice\n");
        return 1;
    }

   
    return 0;
}
