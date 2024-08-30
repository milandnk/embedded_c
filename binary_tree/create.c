//in this code is use for create a node

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *create_node(int data)
{
    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}
int main()
{
    struct node *p = create_node(2);
    struct node *p1 = create_node(1);
    struct node *p2 = create_node(4);

    p->left = p1;
    p->right =p2;
}