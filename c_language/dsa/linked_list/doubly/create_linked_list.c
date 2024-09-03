//tis code is usefull for create doubly linked list

#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *prev;
    int data;
    struct node *next;
};

struct node* add_node(struct node *head,int data){
    struct node *temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
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
    head = (struct node*)malloc(sizeof(struct node));
    head=add_node(head,13);
    
    print_ll(head);
}
