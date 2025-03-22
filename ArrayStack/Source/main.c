#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Stack stack;

    // Khởi tạo Stack với kích thước 5
    init_Stack(&stack, 5);

    // Thêm các phần tử vào Stack
    push_Stack(&stack, 10);
    push_Stack(&stack, 20);
    push_Stack(&stack, 30);
    push_Stack(&stack, 40);
    push_Stack(&stack, 50);
    push_Stack(&stack, 60);
    push_Stack(&stack, 70);
    push_Stack(&stack, 80);

    // Hiển thị Stack sau khi thêm các phần tử
    printf("Stack sau khi thêm các phần tử:\n");
    display_Stack(stack);

    // Xóa 2 phần tử từ Stack
    pop_Stack(&stack);
    pop_Stack(&stack);
    
    // In ra giá trị tại đỉnh của Stack
    printf("Giá trị tại đỉnh Stack: %d\n", get_Stack(stack));

    // Giải phóng bộ nhớ đã cấp phát cho Stack
    free(stack.item);

    return 0;
}
