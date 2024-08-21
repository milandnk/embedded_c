#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *prev;
    int data;
    struct node *next;
};

struct node *add_node(struct node *head, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = head;
    temp->prev = NULL;
    if (head != NULL)
        head->prev = temp;
    head = temp;
    return head;
}

struct node *rev(struct node *head) {
    struct node *temp = NULL;
    struct node *current = head;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; 
    }

    if (temp != NULL)
        head = temp->prev;

    return head;
}

struct node *add_node_last(struct node *head, int data) {
    struct node *last = (struct node *)malloc(sizeof(struct node));
    last->data = data;
    last->next = NULL;

    if (head == NULL) {
        last->prev = NULL;
        return last;
    }

    struct node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = last;
    last->prev = temp;

    return head;
}

void print_ll(struct node *n) {
    while (n != NULL) {
        printf("%d -> ", n->data);
        n = n->next;
    }
    printf("NULL\n");
}

int main() {
    struct node *head = NULL;

    head = add_node(head, 13);
    print_ll(head);

    head = add_node_last(head, 55);
    print_ll(head);

    head = add_node_last(head, 5556);
    print_ll(head);

    head = rev(head);
    print_ll(head);

    return 0;
}
