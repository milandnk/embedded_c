//this program is count to howmany node available in linked list

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

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

    head = (struct node*)malloc(sizeof(struct node));
    second = (struct node*)malloc(sizeof(struct node));
    third  = (struct node*)malloc(sizeof(struct node));

    if (head == NULL || second == NULL || third == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit the program if memory allocation fails
    }

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;
    
    printf("Count of nodes: %d\n", count(head));  // Added newline for readability

    // Free the allocated memory
    free(third);
    free(second);
    free(head);

    return 0;
}
