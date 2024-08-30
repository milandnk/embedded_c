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
    return q->f == q->r;
}

int is_full(struct queue *q)
{
    return (q->r + 1) % q->size == q->f;
}

int dequeue(struct queue *q)
{
    if (is_empty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    else
    {
        q->f = (q->f + 1) % q->size;
        int data = q->arr[q->f];
        return data;
    }
}

void print_q(struct queue *q)
{
    if (is_empty(q))
    {
        printf("Queue is empty\n");
    }
    else
    {
        int i = (q->f + 1) % q->size;
        while (i != (q->r + 1) % q->size)
        {
            printf("%d\t", q->arr[i]);
            i = (i + 1) % q->size;
        }
        printf("\n");
    }
}

void enqueue(struct queue *q, int val)
{
    if (is_full(q))
    {
        printf("Queue is full\n");
    }
    else
    {
        q->r = (q->r + 1) % q->size;
        q->arr[q->r] = val;
    }
}

int main()
{
    struct queue q;
    q.size = 5; // Adjust size for effective circular buffer
    q.f = 0;
    q.r = 0;
    q.arr = (int *)malloc(q.size * sizeof(int));

    enqueue(&q, 5);
    print_q(&q);
    enqueue(&q, 7);
    print_q(&q);
    enqueue(&q, 6);
    print_q(&q);
    enqueue(&q, 4);
    print_q(&q);
    enqueue(&q, 3);
    print_q(&q);

    dequeue(&q);
    print_q(&q);

    enqueue(&q, 8);
    print_q(&q);

    // Free allocated memory
    free(q.arr);

    return 0;
}
