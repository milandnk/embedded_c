#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
struct node *add_last_node(struct node *tail, int data)
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
        tail = new_node;
    }

    return tail;
}
struct node *add_cer_pos(struct node *tail, int data, int pos) // after pos
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr = tail->next;
    if (tail == new_node)
    {
        new_node->next = tail->next;
        tail->next = new_node;
        tail = new_node;
        return tail;
    }
    else
    {
        while (pos > 1)
        {
            ptr = ptr->next;
            pos--;
        }
        new_node->next = ptr->next;
        ptr->next = new_node;
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
    int pos = 2;
    tail = add_last_node(tail, 12);
    tail = add_last_node(tail, 11);
    tail = add_last_node(tail, 10);

    print_ll(tail);

    printf("Count of nodes after adding: %d\n", count(tail));
    tail = add_cer_pos(tail, 5, pos);
    print_ll(tail);

    printf("Count of nodes after adding: %d\n", count(tail));

    return 0;
}
