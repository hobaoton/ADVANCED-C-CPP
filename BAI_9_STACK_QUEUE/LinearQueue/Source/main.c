#include "..\\Header\\LinearQueue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    LinearQueue_Type queue;
    int size = 7;
    
    // Khởi tạo hàng đợi với kích thước size
    LinearQueue_Init(&queue, size);

    // Thêm các phần tử vào hàng đợi
    LinearQueue_Enqueue(&queue, 10);
    LinearQueue_Enqueue(&queue, 20);
    LinearQueue_Enqueue(&queue, 30);
    LinearQueue_Enqueue(&queue, 40);
    LinearQueue_Enqueue(&queue, 50);

    // Hiển thị hàng đợi sau khi thêm các phần tử
    printf("Hàng đợi sau khi thêm 5 phần tử:\n");
    LinearQueue_Display(&queue);
    printf("\n");

    // Xóa 2 phần tử khỏi hàng đợi
    LinearQueue_Dequeue(&queue);
    LinearQueue_Dequeue(&queue);

    // Hiển thị lại hàng đợi sau khi xóa
    printf("Hàng đợi sau khi xóa 2 phần tử:\n");
    LinearQueue_Display(&queue);
    printf("\n");

    // Thêm các phần tử mới vào hàng đợi
    LinearQueue_Enqueue(&queue, 60);
    LinearQueue_Enqueue(&queue, 70);
    LinearQueue_Enqueue(&queue, 80);
    LinearQueue_Enqueue(&queue, 90);
    LinearQueue_Enqueue(&queue, 100);

    // Hiển thị lại hàng đợi sau khi thêm phần tử mới
    printf("Hàng đợi sau khi thêm các phần tử khác:\n");
    LinearQueue_Display(&queue);
    printf("\n");

    // Giải phóng bộ nhớ đã cấp phát cho hàng đợi
    free(queue.item);

    return 0;
}
