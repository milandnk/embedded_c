//ascending order
#include <stdio.h>
void print_arr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

void selection_Sort(int *arr, int n)
{
    int min;
    for (int i = 0; i <= n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j <= n - 1; j++)
        {
            if (arr[min] > arr[j])
            {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main()
{
    int arr[7] = {12, 5, 2, 63, 6, 5, 45};
    int n = 7;
    print_arr(arr, n);
    printf("\n");
    selection_Sort(arr, n);
    printf("ascending order is:\n");
    print_arr(arr, n);

    return 0;
}