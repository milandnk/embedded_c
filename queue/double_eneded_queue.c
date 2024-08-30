//this code of double ended queue 
//it has various functionality like init,insertion and deletion from both end

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Deque
{
    int arr[MAX];
    int front;
    int rear;
};

void initDeque(struct Deque *dq)
{
    dq->front = -1;
    dq->rear = -1;
}

int is_empty(struct Deque *dq)
{
    return (dq->front == -1);
}

int is_full(struct Deque *dq)
{
    return (dq->rear == MAX - 1);
}

void insertFront(struct Deque *dq, int val)
{
    if (is_full(dq))
    {
        printf("Deque is full\n");
        return;
    }
    if (is_empty(dq))
    {
        dq->front = dq->rear = 0;
    }
    else if (dq->front == 0)
    {
        return;
    }
    else
    {
        dq->front--;
    }
    dq->arr[dq->front] = val;
}

int deleteFront(struct Deque *dq)
{
    if (is_empty(dq))
    {
        return 0;
    }
    else if (dq->front == 0)
    {
        dq->front = 1;
    }
    else
    {
        dq->front++;
    }
    return dq->arr[dq->front - 1];
}

int delete_end(struct Deque *dq)
{
    if (is_empty(dq))
    {
        return 0;
    }
    else
    {
        dq->rear--;
    }
    return dq->arr[dq->rear +1];
}

void insertRear(struct Deque *dq, int val)
{
    if (is_full(dq))
    {
        printf("Deque is full\n");
        return;
    }
    if (is_empty(dq))
    {
        dq->front = dq->rear = 0;
    }
    else
    {
        dq->rear++;
    }
    dq->arr[dq->rear] = val;
}

void print_q(struct Deque *dq)
{
    for (int i = dq->front; i <= dq->rear; i++)
    {
        printf("%d\t", dq->arr[i]);
    }
    printf("\n");
}

int main()
{
    struct Deque dq;
    initDeque(&dq);

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    deleteFront(&dq);
    insertRear(&dq, 30);
    delete_end(&dq);
    insertRear(&dq, 40);
    insertFront(&dq, 1);

    print_q(&dq);

    return 0;
}
