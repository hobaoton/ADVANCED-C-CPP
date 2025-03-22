#include <stdio.h>
#include "..\\Header\\single_List.h"

int main() {
    // Tạo các node ban đầu
    Node *head = create_Node(2);
    Node *second = create_Node(28);
    Node *third = create_Node(21);
    Node *four = create_Node(25);

    // Liên kết các node lại với nhau
    head->next = second;
    second->next = third;
    third->next = four;

    // Thêm phần tử vào cuối danh sách
    push_back(&head, 52);
    printf("Danh sach sau khi push_back:\n");
    display(head);
    printf("\n");
    
    // Xóa phần tử cuối danh sách
    pop_back(&head);
    printf("Danh sach sau khi pop_back:\n");
    display(head);
    printf("\n");

    // Thêm phần tử vào đầu danh sách
    push_front(&head, 13);
    printf("Danh sach sau khi push_front:\n");
    display(head);
    printf("\n");

    // Xóa phần tử đầu danh sách
    pop_front(&head);
    printf("Danh sach sau khi pop_front:\n");
    display(head);
    printf("\n");

    // Chèn phần tử tại vị trí cho trước (ví dụ: chèn tại vị trí 1)
    insert(&head, 10, 1);
    printf("Danh sach sau khi insert:\n");
    display(head);
    printf("\n");

    // Xóa phần tử tại vị trí cho trước (ví dụ: xóa node tại vị trí 1)
    erase(&head, 1);
    printf("Danh sach sau khi erase:\n");
    display(head);
    printf("\n");

    // Lấy giá trị node đầu tiên và cuối cùng
    int value_Node = front(head);
    printf("Gia tri Node dau tien: %d\n", value_Node);
    value_Node = back(head);
    printf("Gia tri Node cuoi cung: %d\n", value_Node);

    // Lấy giá trị của node tại vị trí 2
    get(head, 2);

    // Xóa toàn bộ danh sách
    clear(&head);
    printf("Danh sach sau khi clear:\n");
    display(head);
    printf("Danh sach da bi thu hoi!\n");

    return 0;
}
