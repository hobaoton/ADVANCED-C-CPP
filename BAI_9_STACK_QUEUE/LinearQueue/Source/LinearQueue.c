#include "..\\Header\\LinearQueue.h"
#include <stdio.h>
#include <stdlib.h>

/*==============================================================================
**  Định nghĩa các hàm
==============================================================================*/
void LinearQueue_Init(LinearQueue_Type *queue, int size)
{
    if (queue != NULL)
    {
        queue->item = (int*)malloc(size * sizeof(int));
        if (queue->item != NULL)
        {
            queue->size = size;
            queue->front = -1;
            queue->rear = -1;
        }
        else
        {
            /* Xử lý lỗi cấp phát bộ nhớ nếu cần */
            printf("Lỗi: Không cấp phát được bộ nhớ cho hàng đợi.\n");
        }
    }
}

bool LinearQueue_Empty(const LinearQueue_Type *queue)
{
    return ((queue != NULL) && (queue->front == -1));
}

bool LinearQueue_Full(const LinearQueue_Type *queue)
{
    return ((queue != NULL) && (queue->rear == queue->size - 1));
}

void LinearQueue_Enqueue(LinearQueue_Type *queue, int data)
{
    if (queue == NULL)
    {
        return;
    }

    if (LinearQueue_Full(queue))
    {
        printf("Hàng đợi đã đầy! Không thể thêm phần tử.\n");
        return;
    }
    if (LinearQueue_Empty(queue))
    {
        queue->front = 0;
        queue->rear = 0;
    }
    else
    {
        queue->rear++;
    }
    queue->item[queue->rear] = data;
    printf("Đã thêm giá trị %d vào vị trí %d.\n", data, queue->rear);
}

void LinearQueue_Dequeue(LinearQueue_Type *queue)
{
    if ((queue == NULL) || (LinearQueue_Empty(queue)))
    {
        printf("Hàng đợi rỗng! Không thể xóa phần tử.\n");
        return;
    }
    printf("Phần tử tại vị trí %d có giá trị %d đã được xóa khỏi hàng đợi.\n", 
           queue->front, queue->item[queue->front]);
    if (queue->front < queue->rear)
    {
        queue->front++;
    }
    else
    {
        /* Khi chỉ còn 1 phần tử, reset lại hàng đợi */
        queue->front = -1;
        queue->rear  = -1;
    }
}

void LinearQueue_Display(const LinearQueue_Type *queue)
{
    if ((queue == NULL) || (LinearQueue_Empty(queue)))
    {
        printf("Hàng đợi rỗng!\n");
        return;
    }
    for (int i = queue->front; i <= queue->rear; i++)
    {
        printf("Vị trí %d, Giá trị %d\n", i, queue->item[i]);
    }
}
