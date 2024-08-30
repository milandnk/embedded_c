#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};
int flag;
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
struct node *insert(struct node *root, int key)
{
    struct node *prev = NULL;
    if (root == NULL)
    {
        return create_node(key);
    }

    if (key != -1 && !flag)
    {
        prev = root;
        root->left = insert(root->left, key);
    }
    else if (key == -1)
    {
        flag = 1;
    }
    else if (flag)
    {
        prev->right = insert(prev->right, key);
        flag = 0;
    }
    else
    {
        printf("Insertion not possible: key %d already exists.\n", key);
    }

    return root;
}
struct node *create_tree()
{
    int x;
    struct node *newNode = NULL;

    printf("Enter value (-1 for no node): ");
    scanf("%d", &x);

    if (x == -1)
    {
        return NULL;
    }
    newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    newNode->data = x;

    printf("Enter left child of %d:\n", x);
    newNode->left = create_tree();

    printf("Enter right child of %d:\n", x);
    newNode->right = create_tree();

    return newNode;
}
void print_bst(struct node *root, int space)
{
    if (root == NULL)
    {
        return;
    }

    space += 5;

    print_bst(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    print_bst(root->left, space);
}

void draw_bst(struct node *root)
{
    print_bst(root, 0);
}
int main()
{
    int val, n;
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p = NULL;
    while (1)
    {
        printf("Enter value to create(1),delete(2),insert(3),exit(4): ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:

            printf("create tree!!\n");
            p = create_tree();
            draw_bst(p);
            printf("\n");
            printf("inorder:");
            in_order(p);
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &val);
            delete (p, val);
            draw_bst(p);
            printf("\n");
            printf("inorder:");
            in_order(p);
            break;

        case 3:
            printf("Enter value to insert: ");
            scanf("%d", &val);
            insert(p, val);
            draw_bst(p);
            printf("\n");
            printf("inorder:");
            in_order(p);

        case 4:
            exit(1);
        default:
            printf("not valid please resend the number");
            break;
        }
    }
    free(p);

    return 0;
}