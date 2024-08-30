//this code is usefull for paranthesis matchinbg ingiven expression all bracket ({}[])


#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int size;
    int top;
    char *arr;
};

int isEmpty(struct stack *ptr)
{
    return ptr->top == -1;
}

int isFull(struct stack *ptr)
{
    return ptr->top == ptr->size - 1;
}

void push(struct stack *ptr, char val)
{
    if (isFull(ptr))
    {
        printf("Stack Overflow! Cannot push %c to the stack\n", val);
    }
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}

char pop(struct stack *ptr)
{
    if (isEmpty(ptr))
    {
        printf("Stack Underflow! Cannot pop from the stack\n");
        return -1;
    }
    else
    {
        char val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

int match(char a, char b)
{
    if ((a == '{' && b == '}') || (a == '(' && b == ')') || (a == '[' && b == ']'))
    {
        return 1;
    }
    return 0;
}

int parenthesisMatch(char *exp)
{
    struct stack *sp = (struct stack *)malloc(sizeof(struct stack));
    sp->size = 100;
    sp->top = -1;
    sp->arr = (char *)malloc(sp->size * sizeof(char));

    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
        {
            push(sp, exp[i]);
        }
        else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if (isEmpty(sp))
            {
                free(sp->arr);
                free(sp);
                return 0;
            }
            char pop_ch = pop(sp);
            if (!match(pop_ch, exp[i]))
            {
                free(sp->arr);
                free(sp);
                return 0;
            }
        }
        else
        {
            continue;
        }
    }
    return isEmpty(sp);
}

int main()
{
    char *exp = "{(8)(9)}";
    if (parenthesisMatch(exp))
    {
        printf("The parenthe matching\n");
    }
    else
    {
        printf("The parenthe not matching\n");
    }
    return 0;
}
