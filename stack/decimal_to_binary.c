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
    for (int i = n - 1; i >= 0; i--)
    {
        printf("%d\t", arr[i]);
    }
}

int dectobin(int number)
{
    unsigned int num;
    int i = 2;
    if (number == 0)
    {
        printf("not valid");
    }
    else if (number < 0)
    {
        bool k;
        num = (unsigned int)number;
        while (num != 0)
        {
            top++;
            // if (num % i == 1)
            // {
            //     k = 0;
            // }
            // else if (num % i == 0)
            // {
            //     k = 1;
            // }
            stack_arr[top] = num % i;
            num = num / i;
        }
    }
    else if (number > 0)
    {
        
        while (number != 0)
        {
            top++;
            stack_arr[top] = number % i;
            number = number / i;
        }
    }

    print_arr(top + 1, stack_arr);
}
int main()
{
    int number;
    printf("enter dec number:");
    scanf("%d", &number);
    
    dectobin(number);
}