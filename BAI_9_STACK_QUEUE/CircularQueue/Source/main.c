#include "..\\Header\\Circular_Queue.h"

int main()
{
    CircularQueue queue;
    queue_Init(&queue, 5);

    enqueue(&queue, 10);
    enqueue(&queue, 15);
    enqueue(&queue, 20);
    enqueue(&queue, 25);
    enqueue(&queue, 30);

    display(queue);
    printf("\n");
    
    printf("Front element: %d\n", front(queue));
    printf("\n");
    printf("Rear element: %d\n", rear(queue));
    printf("\n");

    printf("Dequeued %d\n", dequeue(&queue));
    printf("\n");

    display(queue);
    printf("\n");

    enqueue(&queue, 50);
    display(queue);
    printf("\n");
    
    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n", rear(queue));

    return 0;
}
