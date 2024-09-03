#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr;
    ptr = (int *)malloc(5 * sizeof(int));

    if (ptr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    ptr[0] = 1;
    ptr[1] = 3;
    ptr[2] = 5;
    ptr[3] = 7;
    ptr[4] = 9;

    printf("Original values: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", ptr[i]);
    }
    printf("\n");

    ptr = realloc(ptr, 7 * sizeof(int));

    if (ptr == NULL)
    {
        printf("Memory reallocation failed.\n");
        return 1;
    }

    ptr[5] = 10;
    ptr[6] = 11;

    printf("New values: ");
    for (int i = 0; i < 7; i++)
    {
        printf("%d\t", ptr[i]);
    }
    printf("\n");

    free(ptr); // Don't forget to free the allocated memory
    return 0;
}
