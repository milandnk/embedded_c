#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void add_last_node(struct node *n, int data) {
    struct node *ptr = n;
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    temp->data = data;
    temp->next = NULL;

    // Traverse to the last node
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    // Attach the new node at the end
    ptr->next = temp;
}

int count(struct node *n) {
    struct node *ptr = n;
    int cnt = 0;
    while (ptr != NULL) {
        ptr = ptr->next;
        cnt++;
    }
    return cnt;
}

int main() {
    struct node *head = NULL;
    struct node *second = NULL;
    struct node *third = NULL;

    head = (struct node *)malloc(sizeof(struct node));
    second = (struct node *)malloc(sizeof(struct node));
    third = (struct node *)malloc(sizeof(struct node));

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

    printf("Count of nodes before adding: %d\n", count(head));

    add_last_node(head, 13); // Add a new node with data = 13 at the end

    printf("Count of nodes after adding: %d\n", count(head));

    // Free the allocated memory
    // free(third->next); 
    free(third);
    free(second);
    free(head);

    return 0;
}
