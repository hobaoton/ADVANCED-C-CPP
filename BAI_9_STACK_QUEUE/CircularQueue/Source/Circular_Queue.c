#include "..\\Header\\Circular_Queue.h"

// Khởi tạo hàng đợi
void queue_Init(CircularQueue *queue, int size)
{
    queue->items = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
}

// Kiểm tra hàng đợi rỗng
int queue_IsEmpty(CircularQueue queue)
{
    return (queue.front == -1);
}

// Kiểm tra hàng đợi đầy
int queue_IsFull(CircularQueue queue)
{
    return (queue.rear + 1) % queue.size == queue.front;
}   //  0   1     2      3        4
    //      rear  front
// Thêm phần tử vào cuối hàng đợi
void enqueue(CircularQueue *queue, int data)
{
    if (queue_IsFull(*queue))
    {
        printf("Hang doi day!\n");
    }
    else
    {
        if (queue->front == -1)
        {
            queue->front = queue->rear = 0;
        }
        else
        {
            queue->rear = (queue->rear + 1) % queue->size;
            // 0   1   2   3   4   
            //         15  20  25  
        }
        queue->items[queue->rear] = data;
        printf("Enqueued %d\n", data);
    }
}

// Xóa phần tử từ đầu hàng đợi
int dequeue(CircularQueue *queue)
{
    if (queue_IsEmpty(*queue))
    {
        printf("Hang doi rong\n");
        return QUEUE_EMPTY;
    }
    else
    {
        int dequeue_value = queue->items[queue->front];
        if (queue->front == queue->rear)
        {
            queue->front = queue->rear = -1;
        }
        else
        {
            queue->front = (queue->front + 1) % queue->size;
        }// 0   1   2   3   4
        //  20  25          30
        return dequeue_value;
    }
}

// Lấy giá trị phần tử đầu hàng đợi
int front(CircularQueue queue)
{
    if (queue_IsEmpty(queue))
    {
        printf("Hang doi rong\n");
        return QUEUE_EMPTY;
    }
    return queue.items[queue.front];
}

// Lấy giá trị phần tử cuối hàng đợi
int rear(CircularQueue queue)
{
    if (queue_IsEmpty(queue))
    {
        printf("Hang doi rong\n");
        return QUEUE_EMPTY;
    }
    return queue.items[queue.rear];
}

// Hiển thị hàng đợi
void display(CircularQueue queue)
{
    if (queue_IsEmpty(queue))
    {
        printf("Hang doi rong\n");
        return;
    }

    printf("Hang doi: ");
    int i = queue.front;
    while (1)
    {
        printf("%d ", queue.items[i]);
        if (i == queue.rear) break;
        i = (i + 1) % queue.size;
    }// 0   1   2   3   4
    //  20  25          30
    printf("\n");
}
