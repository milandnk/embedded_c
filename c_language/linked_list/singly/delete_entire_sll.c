#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
//using two pointer
// struct node *delete_last_node(struct node *head)
// {
//     if (head == NULL)  // Check if the list is empty
//         return NULL;

//     if (head->next == NULL)  // If there's only one node
//     {
//         free(head);
//         return NULL;
//     }

//     struct node *ptr = head;
//     struct node *ptr1 = NULL;

//     while (ptr->next != NULL)
//     {
//         ptr1 = ptr;
//         ptr = ptr->next;
//     }

//     ptr1->next = NULL;  
//     free(ptr); 

//     return head;
// }
//using 1 pointer
struct node *delete_entire_node(struct node *head)
{
    struct node *ptr = head;
    while (ptr !=NULL)
    {
        ptr = ptr->next;
        free(head);
        head = ptr;
    }
   
    free(ptr); 
    free(head); 
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

    int node = count(head);
    printf("Count of nodes before adding: %d\n", count(head));
    print_ll(head);

    // head = delete_last_node(head);
    head = delete_entire_node(head);

    printf("Count of nodes after adding: %d\n", count(head));
    print_ll(head);
  
    free(second);
    free(head);

    return 0;
}

