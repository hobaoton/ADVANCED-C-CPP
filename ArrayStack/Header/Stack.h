#ifndef STACK_H
#define STACK_H
/*==============================================================================
**  Dự án  : MyAutosarProject
**  Module : Stack
**  File   : Stack.h
**  Mô tả  : Header file cho module Stack, định nghĩa cấu trúc và khai báo hàm
**
**  (c) Bản quyền thuộc về YourCompany. Mọi quyền được bảo lưu.
==============================================================================*/

/* THƯ VIỆN CẦN THIẾT */
#include <stdbool.h>

/*==============================================================================
**  Kiểu dữ liệu và cấu trúc toàn cục
==============================================================================*/
typedef struct Stack
{
    int *item;    /* Con trỏ đến mảng chứa các phần tử của Stack */
    int size;     /* Kích thước tối đa của Stack */
    int top;      /* Chỉ số đỉnh của Stack */
} Stack;

/*==============================================================================
**  Khai báo hàm
==============================================================================*/
/**
 * @brief Khởi tạo Stack với kích thước xác định.
 * @param stack Con trỏ đến instance của Stack.
 * @param size Kích thước tối đa của Stack.
 */
void init_Stack (Stack *stack, int size);

/**
 * @brief Kiểm tra Stack có rỗng không.
 * @param stack Instance của Stack.
 * @return true nếu Stack rỗng, false nếu không.
 */
bool empty_Stack (Stack stack);

/**
 * @brief Kiểm tra Stack có đầy không.
 * @param stack Instance của Stack.
 * @return true nếu Stack đầy, false nếu không.
 */
bool full_Stack (Stack stack);

/**
 * @brief Thêm một phần tử vào Stack.
 * @param stack Con trỏ đến instance của Stack.
 * @param data Giá trị cần thêm.
 */
void push_Stack (Stack *stack, int data);

/**
 * @brief Xóa phần tử khỏi Stack.
 * @param stack Con trỏ đến instance của Stack.
 */
void pop_Stack (Stack *stack);

/**
 * @brief Lấy giá trị tại đỉnh Stack.
 * @param stack Instance của Stack.
 * @return Giá trị tại đỉnh Stack hoặc -1 nếu Stack rỗng.
 */
int get_Stack (Stack stack);

/**
 * @brief Hiển thị các phần tử trong Stack.
 * @param stack Instance của Stack.
 */
void display_Stack (Stack stack);

#endif /* STACK_H */
