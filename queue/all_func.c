// #include <stdio.h>
// #include <stdlib.h>

// struct queue
// {
//     int f;
//     int r;
//     int *arr;
//     int size;
// };

// int is_empty(struct queue *q)
// {
//     if (q->f == q->r)
//     {
//         return 1;
//     }
//     return 0;
// }

// int is_full(struct queue *q)
// {
//     if (q->r == q->size - 1)
//     {
//         return 1;
//     }
//     return 0;
// }
// int dequeue(struct queue *q)
// {
//     if (is_empty(q))
//     {
//         printf("queue is empty");
//     }
//     else
//     {
//         q->f++;
//         int data = q->arr[q->f];
//         return data;
//     }
// }

// void print_q(struct queue *q)
// {
//     for (int i = q->f+1; i <= q->r; i++)
//     {
//         printf("%d\t", q->arr[i]);
//     }
//     printf("\n");
// }
// void enqueue(struct queue *q , int val)
// {
//     if (is_full(q))
//     {
//         printf("queue is full");
//     }
//     else
//     {
//         q->r++;
//         q->arr[q->r] = val;
//     }
// }

// int main()
// {
//     struct queue *q;
//     q->size = 10;
//     q->f = -1;
//     q->r = -1;
//     q->arr = (int *)malloc(q->size * sizeof(int));

//     enqueue(q , 5);
//     print_q(q);
//     enqueue(q , 7);
//     print_q(q);
//     enqueue(q , 6);
//     print_q(q);
//     enqueue(q , 4);
//     print_q(q);
//     enqueue(q , 3);
//     print_q(q);
//     dequeue(q);
//     print_q(q);


//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int f;
    int r;
    int *arr;
    int size;
};

int is_empty(struct queue *q)
{
    if (q->f == q->r)
    {
        return 1;
    }
    return 0;
}

int is_full(struct queue *q)
{
    if (q->r == q->size - 1)
    {
        return 1;
    }
    return 0;
}
int dequeue(struct queue *q)
{
    if (is_empty(q))
    {
        printf("queue is empty");
    }
    else
    {
        q->f++;
        int data = q->arr[q->f];
        return data;
    }
}

void print_q(struct queue *q)
{
    for (int i = q->f+1; i <= q->r; i++)
    {
        printf("%d\t", q->arr[i]);
    }
    printf("\n");
}
void enqueue(struct queue *q , int val)
{
    if (is_full(q))
    {
        printf("queue is full");
    }
    else
    {
        q->r++;
        q->arr[q->r] = val;
    }
}

int main()
{
    struct queue q;
    q.size = 10;
    q.f = -1;
    q.r = -1;
    q.arr = (int *)malloc(q.size * sizeof(int));

    enqueue(&q , 5);
    print_q(&q);
    enqueue(&q , 7);
    print_q(&q);
    enqueue(&q , 6);
    print_q(&q);
    enqueue(&q , 4);
    print_q(&q);
    enqueue(&q , 3);
    print_q(&q);
    dequeue(&q);
    print_q(&q);


    return 0;
}