#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *add_first_node(struct node *head, int data)
{
    struct node *ptr;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;

    ptr->next = head;
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

struct node *set_evodd(struct node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    struct node *ptr = head;
    struct node *ptr1 = head->next;
    struct node *head1 = ptr1;

    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr->next = ptr1->next;
        ptr = ptr1->next;
        ptr1->next = ptr->next;
        ptr1 = ptr->next;
    }

    ptr->next = head1;
    return head;
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

    head = add_first_node(head, 13);

    printf("Count of nodes after adding: %d\n", count(head));
    print_ll(head);

    head = set_evodd(head);
    printf("Count of nodes after adding: %d\n", count(head));
    print_ll(head);

    free(third);
    free(second);
    free(head);

    return 0;
}
