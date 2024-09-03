#include <stdio.h>

void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

void rotate_a_left(int a[], int b[], int n, int step)
{
    for (int i = 0; i < step; i++)
    {
        b[i] = a[i];
    }
    for (int j = 0; j < n - step; j++)
    {
        a[j] = a[j + step];
    }
    for (int k = 0; k < step; k++)
    {
        a[n - step + k] = b[k];
    }
    print_arr(a, n);
}

void rotate_a_right(int a[], int b[], int n, int step)
{
    for (int i = n - step, j = 0; i < n; i++, j++)
    {
        b[j] = a[i];
    }
    for (int j = n - step - 1; j >= 0; j--)
    {
        a[j + step] = a[j];
    }
    for (int k = 0; k < step; k++)
    {
        a[k] = b[k];
    }
    print_arr(a, n);
}

int main()
{
    int rotate, step;
    int a[] = {1, 2, 3, 4, 5};
    int b[5];
    int n = sizeof(a) / sizeof(a[0]);
    print_arr(a, n);
    printf("\n");
    printf("if left rotation then click 1 right rotation then click 2:");
    scanf("%d", &rotate);
    printf("how many step:");
    scanf("%d", &step);
    // if left rotation then click 1 right rotation then click 2
    switch (rotate)
    {
    case 1:
        rotate_a_left(a, b, n, step);
        break;
    case 2:
        rotate_a_right(a, b, n, step);
        break;
    }

    return 0;
}
