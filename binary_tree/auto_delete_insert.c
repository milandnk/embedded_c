//in this code explain create node,delete and insert function
//in insert function data auto matic set using bst and their value
//in delete function value will be delete ....

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

struct node *inorderpredesseor(struct node *root)
{
    root = root->left;
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
struct node *inorder_predessor(struct node *root)
{
    struct node *current = root->left;
    while (current && current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

struct node *delete(struct node *root, int val)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (val < root->data)
    {
        root->left = delete (root->left, val);
    }
    else if (val > root->data)
    {
        root->right = delete (root->right, val);
    }
    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *ipre = inorder_predessor(root);
        root->data = ipre->data;
        root->left = delete (root->left, ipre->data);
    }

    return root;
}
void insert(struct node *root, int key)
{
    struct node *prev = NULL;
    while (root != NULL)
    {
        prev = root;
        if (root->data == key)
        {
            printf("insertion is not possible");
            return;
        }
        else if (root->data > key)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    struct node *new = create_node(key);
    if (prev->data > key)
    {
        prev->left = new;
    }
    else
    {
        prev->right = new;
    }
}

int main()
{
    int val, n;
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
    while (1)
    {
        printf("Enter value to insert(1),delete(2),exit(3): ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &val);
            insert(p, val);
            in_order(p);
            printf("\n");
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &val);
            delete (p, val);
            in_order(p);
            printf("\n");
            break;
        case 3:
            exit(1);
        default:
            printf("not valid please resend the number");
            break;
        }
    }
    free(p);
    free(p1);
    free(p2);
    free(p3);
    free(p4);

    return 0;
}
