//this code is helpful for reverse entire singly linked list

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *reverse(struct node *head)
{
    struct node *ptr = NULL;
    struct node *ptr2 = NULL;
    while (head != NULL)
    {
        ptr2 = head->next;
        head->next = ptr;
        ptr = head;
        head = ptr2;
    }
    head = ptr;
    return head;
}

void print_ll(struct node *n)
{
    while (n != NULL)
    {
        printf("%d ->", n->data);
        n = n->next;
    }
    printf("NULL\n");
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

int main()
{
    struct node *head = NULL;
    struct node *second = NULL;
    struct node *third = NULL;

    head = (struct node *)malloc(sizeof(struct node));
    second = (struct node *)malloc(sizeof(struct node));
    third = (struct node *)malloc(sizeof(struct node));

    if (head == NULL || second == NULL || third == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printf("Count of nodes before adding: %d\n", count(head));
    print_ll(head);

    head = reverse(head);

    printf("Count of nodes after adding: %d\n", count(head));
    print_ll(head);

    // Free the allocated memory
    // free(third->next);
    free(third);
    free(second);
    free(head);

    return 0;
}
