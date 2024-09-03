//in this function is usefull for find the key using recusion 

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
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void pre_order(struct node *root)
{
    if (root != NULL)
    {
        printf("%d  ", root->data);
        pre_order(root->left);
        pre_order(root->right);
    }
}

void post_order(struct node *root)
{
    if (root != NULL)
    {
        post_order(root->left);
        post_order(root->right);
        printf("%d  ", root->data);
    }
}

void in_order(struct node *root)
{
    if (root != NULL)
    {
        in_order(root->left);
        printf("%d  ", root->data);
        in_order(root->right);
    }
}

int is_bst_util(struct node *root, struct node **prev)
{
    if (root != NULL)
    {
        if (!is_bst_util(root->left, prev))
        {
            return 0;
        }
        if (*prev != NULL && root->data <= (*prev)->data)
        {
            return 0;
        }
        *prev = root;
        return is_bst_util(root->right, prev);
    }
    return 1;
}

int is_bst(struct node *root)
{
    struct node *prev = NULL;
    return is_bst_util(root, &prev);
}

struct node *search(struct node *root, int key)
{
    if (root == NULL || root->data == key)
    {
        return root;
    }
    if (root->data > key)
    {
        return search(root->left, key);
    }
    return search(root->right, key);
}

int main()
{
    int val;
    struct node *p = create_node(4);
    struct node *p1 = create_node(2);
    struct node *p2 = create_node(1);
    struct node *p3 = create_node(3);
    struct node *p4 = create_node(5);

    p->left = p1;
    p->right = p4;
    p1->left = p2;
    p1->right = p3;

    in_order(p);
    printf("\n");

    if (is_bst(p))
    {
        printf("This is a BST!!\n");
    }
    else
    {
        printf("This is not a BST!!\n");
    }

    printf("Enter value to find: ");
    scanf("%d", &val);
    struct node *n = search(p, val);

    if (n != NULL)
    {
        printf("Value %d is available!!\n", val);
    }
    else
    {
        printf("Value %d is not available!!\n", val);
    }

    free(p);
    free(p1);
    free(p2);
    free(p3);
    free(p4);

    return 0;
}
