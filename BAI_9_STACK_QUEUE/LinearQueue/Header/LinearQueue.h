#ifndef LINEARQUEUE_H
#define LINEARQUEUE_H
/*==============================================================================
**  Dự án  : MyAutosarProject
**  Module : LinearQueue
**  File   : LinearQueue.h
**  Mô tả : Header file cho các thao tác với hàng đợi tuyến tính
**
**  (c) Bản quyền thuộc về YourCompany. Mọi quyền được bảo lưu.
==============================================================================*/

/* THƯ VIỆN CẦN THIẾT */
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
**  Kiểu dữ liệu và cấu trúc toàn cục
==============================================================================*/
typedef struct
{
    int *item;     /* Con trỏ đến mảng chứa các phần tử của hàng đợi */
    int size;      /* Kích thước tối đa của hàng đợi */
    int front;     /* Vị trí đầu hàng đợi */
    int rear;      /* Vị trí cuối hàng đợi */
} LinearQueue_Type;

/*==============================================================================
**  Khai báo hàm
==============================================================================*/
/**
 * @brief   Khởi tạo hàng đợi tuyến tính với kích thước xác định.
 * @param   queue   Con trỏ đến instance của LinearQueue_Type.
 * @param   size    Kích thước tối đa của hàng đợi.
 */
void LinearQueue_Init(LinearQueue_Type *queue, int size);

/**
 * @brief   Kiểm tra hàng đợi có rỗng không.
 * @param   queue   Con trỏ đến instance của LinearQueue_Type.
 * @return  true nếu hàng đợi rỗng, false nếu không.
 */
bool LinearQueue_Empty(const LinearQueue_Type *queue);

/**
 * @brief   Kiểm tra hàng đợi có đầy không.
 * @param   queue   Con trỏ đến instance của LinearQueue_Type.
 * @return  true nếu hàng đợi đầy, false nếu không.
 */
bool LinearQueue_Full(const LinearQueue_Type *queue);

/**
 * @brief   Thêm (enqueue) một phần tử vào hàng đợi.
 * @param   queue   Con trỏ đến instance của LinearQueue_Type.
 * @param   data    Giá trị cần thêm vào hàng đợi.
 */
void LinearQueue_Enqueue(LinearQueue_Type *queue, int data);

/**
 * @brief   Xóa (dequeue) một phần tử khỏi hàng đợi.
 * @param   queue   Con trỏ đến instance của LinearQueue_Type.
 */
void LinearQueue_Dequeue(LinearQueue_Type *queue);

/**
 * @brief   Hiển thị nội dung của hàng đợi.
 * @param   queue   Con trỏ đến instance của LinearQueue_Type.
 */
void LinearQueue_Display(const LinearQueue_Type *queue);

#ifdef __cplusplus
}
#endif

#endif /* LINEARQUEUE_H */
