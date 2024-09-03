//this is a final code 
//it has deletion,insertion and traversal proscess is done

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *add_first_node(struct node *head, int data, int pos) {
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL; 

    if (pos == 1) {
        new_node->next = head; 
        head = new_node;
        return head;
    }

    struct node *ptr = head;
    for (int i = 1; i < pos - 1 && ptr != NULL; i++) {
        ptr = ptr->next;
    }

    if (ptr != NULL) {
        new_node->next = ptr->next;
        ptr->next = new_node;
    } else {
        printf("Position out of bounds\n");
        free(new_node);
    }

    return head;
}

struct node *delete_cer_node(struct node *head, int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    struct node *ptr1 = head;
    if (pos == 1) { 
        head = head->next;
        free(ptr1);
        return head;
    }

    struct node *ptr = NULL;
    for (int i = 1; i < pos && ptr1 != NULL; i++) {
        ptr = ptr1;
        ptr1 = ptr1->next;
    }

    if (ptr1 != NULL) {
        ptr->next = ptr1->next;
        free(ptr1);
    } else {
        printf("Position out of bounds\n");
    }

    return head;
}

void print_ll(struct node *n) {
    while (n != NULL) {
        printf("%d -> ", n->data);
        n = n->next;
    }
    printf("NULL\n");
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
    int data, position, n;

    while (1) {
        printf("Enter 1 to add, 2 to delete, 3 to exit: ");
        scanf("%d", &n);

        switch (n) {
        case 1:
            printf("Enter value data: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &position);
            head = add_first_node(head, data, position);
            printf("Count of nodes after adding: %d\n", count(head));
            print_ll(head);
            break;
        case 2:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            head = delete_cer_node(head, position);
            printf("Count of nodes after deletion: %d\n", count(head));
            print_ll(head);
            break;
        case 3:
            free(head); 
            exit(0);
        default:
            printf("Not valid, try again\n");
            break;
        }
    }

    return 0;
}
