//delete node at first position

#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *prev;
    int data;
    struct node *next;
};

struct node *add_node(struct node *head, int data)
{
    struct node *temp = NULL;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    head = temp;
    return head;
}

struct node *add_node_last(struct node *head, int data)
{
    struct node *temp = NULL;
    temp = (struct node *)malloc(sizeof(struct node));
    temp = head;
    struct node *last = NULL;
    last = (struct node *)malloc(sizeof(struct node));
    last->data = data;
    last->next = NULL;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    
    temp->next = last;
    last->prev = temp;
    return head;
}

struct node *delete_node_first(struct node *head)
{
    struct node *temp = NULL;
    temp = (struct node *)malloc(sizeof(struct node));
    temp = head->next;
    head->next = NULL;
    free(head);
    head = temp;
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
int main()
{
    struct node *head = NULL;
    head = (struct node *)malloc(sizeof(struct node));
    head = add_node(head, 13);

    print_ll(head);
    head = add_node_last(head, 55);
    print_ll(head);
    head = add_node_last(head, 5556);
    print_ll(head);
    head = delete_node_first(head);
    print_ll(head);
}
