//this is a function of peak,pop,push using array


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 4

int stack_arr[max];
int top = -1;

void push(int data)
{
    if (top == (max - 1))
    {
        printf("stack is overflow");
        return;
    }
    top++;
    stack_arr[top] = data;
}
int pop()
{
    int data;
    if (top == (-1))
    {
        printf("stack is empty");
        exit(1);
    }
    data = stack_arr[top];
    top--;
    return data;
}

int peak()
{
    int data = stack_arr[top];
    return data;
}

bool is_full()
{
    if (top == max - 1)
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
    if (top == -1)
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
    for (int i = 0; i <= (n - 1); i++)
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

    print_arr(top + 1, stack_arr);
    printf("\n");
    data = pop();
    print_arr(top + 1, stack_arr);
}