#include <stdio.h>
#include <stdlib.h>

int top = -1;

struct node
{
    int data;
    struct node *next;
};

struct node *push(struct node *head, int data)
{
    struct node *ptr;
    ptr = (struct node *)malloc(sizeof(struct node));

    if (ptr == NULL)
    {
        printf("Memory allocation failed because not stack full\n");
        return head;
    }
    ptr->data = data;
    ptr->next = NULL;
    top++;
    ptr->next = head;
    head = ptr;
    return head;
}

struct node *pop(struct node *head)
{
    struct node *ptr = head;
    ptr = (struct node *)malloc(sizeof(struct node));
    head = head->next;
    free(ptr);
    ptr = NULL;
    return head;
}

void print_ll(struct node *n)
{
    while (n != NULL)
    {
        printf("%d ->", n->data);
        n = n->next;
    }
int count(struct node *n)
{
    struct node *ptr = n;
    int cnt = 0;
    while (ptr != NULL)
    {
        ptr = ptr->next;
        cnt++;
    }
    return cnt;
}

void reverse(struct node **top) {
    struct node * prev = NULL;
    struct node * curr = *top;
    struct node * next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *top = prev;
}
int main() {
    struct node *head = NULL;

    head = push(head, 1);
    head = push(head, 13);
    head = push(head, 10);

    printf("Count of stack size: %d\n", count(head));
    print_ll(head);

    reverse(&head);
    printf("Count after reversing stack: %d\n", count(head));
    print_ll(head);

    return 0;
}
