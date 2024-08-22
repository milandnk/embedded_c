#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 4

int stack_arr[max];
int first = -1;

void push(int data)
{
    int i;
    first++;
    for (i = first; i > 0; i--)
    {
        stack_arr[i] = stack_arr[i-1];
    }
    stack_arr[0] = data;
}
int pop()
{
    int data,i;
    data = stack_arr[0];
    for (int i = 0; i < first; i++)
    {
        stack_arr[i]=stack_arr[i+1];
    }
    first--;
    return data;
}

int peak()
{
    int data = stack_arr[0];
    return data;
}

bool is_full()
{
    if (first == max - 1)
    {
        printf("function is full!!");
        return 1;
    }
    else
    {
        printf("function is not full!!");
        return 0;
    }
}

bool is_empty()
{
    if (first == -1)
    {
        printf("function is empty!!");
        return 1;
    }
    else
    {
        printf("function is not empty!!");
        return 0;
    }
    
}
void print_arr(int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
}
int main()
{
    int data;

    is_full();
    printf("\n");
    is_empty();
    printf("\n");

    push(2);
    push(20);
    push(36);

    print_arr(first + 1, stack_arr);
    printf("\n");
    data = pop();
    print_arr(first + 1, stack_arr);
}