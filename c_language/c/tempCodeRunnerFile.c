#include <stdio.h>
#include <string.h>

void sort(int n, char *arr[])
{ 
    for (int k = 0; k < n; k++)
    {    

        for (int i = 0; i < n -k- 1; i++)
        {
            if (arr[i]> arr[i + 1]) 
            {
                char *temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", arr[i]);
    }
}

int main()
{
    char *arr[3] = {"apple", "orange", "banana"};

    sort(3, arr);

    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", arr[i]);
    }

    return 0;
}
