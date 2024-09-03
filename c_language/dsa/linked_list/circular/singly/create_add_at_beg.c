// add node at first position

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
struct node *add_first_node(struct node *tail, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;

    if (tail == NULL)
    {
        tail = new_node;
        tail->next = tail; 
    }
    else
    {
        new_node->next = tail->next;
        tail->next = new_node;
    }

    return tail;
}

void print_ll(struct node *tail)
{
    if (tail == NULL)
        return;

    struct node *ptr = tail->next;
    do
    {
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    } while (ptr != tail->next);
    printf("NULL\n");
}
int count(struct node *tail)
{
    if (tail == NULL)
        return 0;

    struct node *ptr = tail->next;
    int cnt = 0;
    do
    {
        cnt++;
        ptr = ptr->next;
    } while (ptr != tail->next);

    return cnt;
}

int main()
{
    struct node *tail = NULL;

    tail = add_first_node(tail, 12);
    tail = add_first_node(tail, 11);
    tail = add_first_node(tail, 10);

    print_ll(tail);

    printf("Count of nodes after adding: %d\n", count(tail));

    return 0;
}
