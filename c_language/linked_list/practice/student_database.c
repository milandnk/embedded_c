#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[15];
    int roll_num;
    char gender;
    struct node *next;
};

void print_data(struct node *head)
{
    struct node *current = head;
    while (current != NULL)
    {
        printf("Name: %s\n", current->name);
        printf("Roll Number: %d\n", current->roll_num);
        printf("Gender: %c\n", current->gender);

        current = current->next;
    }
}

struct node *add(struct node *head)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    printf("Enter student name: ");
    scanf("%s", new_node->name);
    printf("Enter roll number: ");
    scanf("%d", &new_node->roll_num);
    printf("Enter gender (M/F): ");
    scanf(" %c", &new_node->gender);

    new_node->next = head;
    head = new_node;
    return head;
}

struct node *edit(struct node *head, int roll_num)
{
    struct node *current = head;
    while (current != NULL)
    {
        if (current->roll_num == roll_num)
        {
            printf("Editing student with roll number %d\n", roll_num);
            printf("Enter new name: ");
            scanf("%s", current->name);
            printf("Enter new gender (M/F): ");
            scanf(" %c", &current->gender);
            return head;
        }
        current = current->next;
    }
    printf("Student with roll number %d not found.\n", roll_num);
    return head;
}

struct node *delete_student(struct node *head, int roll_num)
{
    struct node *current = head;
    struct node *previous = NULL;

    while (current != NULL && current->roll_num != roll_num)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Student with roll number %d not found.\n", roll_num);
        return head;
    }

    if (previous == NULL)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    free(current);
    printf("Student with roll number %d deleted.\n", roll_num);
    return head;
}

int main()
{
    struct node *head = NULL;
    int i, roll_num;

    while (1)
    {
        printf("\nOptions:\n");
        printf("(1) Add student\n");
        printf("(2) Edit student\n");
        printf("(3) Delete student\n");
        printf("(4) Print student data\n");
        printf("(5) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &i);

        switch (i)
        {
        case 1:
            head = add(head);
            break;
        case 2:
            printf("Enter roll number to edit: ");
            scanf("%d", &roll_num);
            head = edit(head, roll_num);
            break;
        case 3:
            printf("Enter roll number to delete: ");
            scanf("%d", &roll_num);
            head = delete_student(head, roll_num);
            break;
        case 4:
            print_data(head);
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Invalid\n");
            break;
        }
    }

    return 0;
}
