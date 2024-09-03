#include <stdio.h>
void print_arr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

void insertion_Sort(int *arr, int n)
{
    for (int i = 1; i <= n - 1; i++)
    {
        int key;
        int j = i - 1;
        key = arr[i];
        while (j >= 0 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main()
{
    int arr[7] = {12, 5, 2, 63, 6, 5, 45};
    int n = 7;
    print_arr(arr, n);
    printf("\n");
    printf("descending order is:");
    insertion_Sort(arr, n);
    printf("\n");
    print_arr(arr, n);

    return 0;
}