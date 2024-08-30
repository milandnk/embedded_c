//find some value of given node in which position

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
struct node *find(struct node *tail, int data) // after pos
{
    int count = 1;
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr = tail->next;

    while (ptr->data != data)
    {
        ptr = ptr->next;
        count++;
        if (ptr == tail)
        {
            printf("no avilable");
        }
    }
    printf("avil at %d pos\n",count);

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
    tail = find(tail, 11);
    print_ll(tail);

    printf("Count of nodes after adding: %d\n", count(tail));

    return 0;
}
