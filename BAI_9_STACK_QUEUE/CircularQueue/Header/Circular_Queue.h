#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *items; // Mảng lưu trữ phần tử
    int size;   // Kích thước hàng đợi
    int front;  // Vị trí đầu hàng đợi
    int rear;   // Vị trí cuối hàng đợi
} CircularQueue;

#define QUEUE_EMPTY -1

void queue_Init(CircularQueue *queue, int size);
int queue_IsEmpty(CircularQueue queue);
int queue_IsFull(CircularQueue queue);
void enqueue(CircularQueue *queue, int data);
int dequeue(CircularQueue *queue);
int front(CircularQueue queue);
int rear(CircularQueue queue);
void display(CircularQueue queue);

#endif
