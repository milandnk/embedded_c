#include <stdio.h>
void print_arr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

void bubbleSort(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int arr[7] = {12, 5, 2, 63, 6, 5, 45};
    int n = 7;
    print_arr(arr, n);
    bubbleSort(arr, n);
    printf("\n");
    print_arr(arr, n);

    return 0;
}