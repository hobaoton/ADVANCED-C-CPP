#include "..\\Header\\doubly_List.h"

// Kiểm tra danh sách rỗng
bool empty(doubly_List *head) {
    return head == NULL;
}

// Đếm số node trong danh sách
int size_DouList(doubly_List *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Tạo một node mới
doubly_List *create_DouList(int data) {
    doubly_List *new_Node = (doubly_List *)malloc(sizeof(doubly_List));
    new_Node->data = data;
    new_Node->next = NULL;
    new_Node->prev = NULL;
    return new_Node;
}

// Hiển thị danh sách từ đầu đến cuối
void display_FronttoBack(doubly_List *head) {
    if (empty(head)) {
        printf("Danh sach rong!\n");
        return;
    }
    int count = 0;
    while (head != NULL) {
        printf("Node[%d] = %d\n", count, head->data);
        count++;
        head = head->next;
    }
}

// Hiển thị danh sách từ cuối lên đầu
void display_BacktoFront(doubly_List *head) {
    if (empty(head)) {
        printf("Danh sach rong!\n");
        return;
    }
    // Tìm node cuối
    while (head->next != NULL) {
        head = head->next;
    }
    // Hiển thị ngược
    int count = size_DouList(head) - 1;
    while (head != NULL) {
        printf("Node[%d] = %d\n", count, head->data);
        count--;
        head = head->prev;
    }
}

// Thêm vào đầu danh sách
void push_front(doubly_List **head, int data) {
    doubly_List *new_Node = create_DouList(data);
    if (empty(*head)) {
        *head = new_Node;
        return;
    }
    new_Node->next = *head;
    (*head)->prev = new_Node;
    *head = new_Node;
}

// Thêm vào cuối danh sách
void push_back(doubly_List **head, int data) {
    doubly_List *new_Node = create_DouList(data);
    if (empty(*head)) {
        *head = new_Node;
        return;
    }
    doubly_List *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_Node;
    new_Node->prev = temp;
}

// Xóa node đầu tiên
void pop_front(doubly_List **head) {
    if (empty(*head)) {
        printf("Danh sach rong!\n");
        return;
    }
    doubly_List *temp = *head;
    *head = (*head)->next;
    if (*head) (*head)->prev = NULL;
    free(temp);
}

// Xóa node cuối cùng
void pop_back(doubly_List **head) {
    if (empty(*head)) {
        printf("Danh sach rong!\n");
        return;
    }
    doubly_List *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->prev) temp->prev->next = NULL;
    else *head = NULL; // Nếu danh sách chỉ có một phần tử
    free(temp);
}

// Chèn node vào vị trí bất kỳ
void insert(doubly_List **head, int data, int vitri) {
    if (vitri < 0 || vitri > size_DouList(*head)) {
        printf("Vi tri khong hop le!\n");
        return;
    }
    if (vitri == 0) {
        push_front(head, data);
        return;
    }
    doubly_List *new_Node = create_DouList(data);
    doubly_List *temp = *head;
    for (int i = 0; i < vitri - 1; i++) {
        temp = temp->next;
    }
    new_Node->next = temp->next;
    if (temp->next) temp->next->prev = new_Node;
    temp->next = new_Node;
    new_Node->prev = temp;
}

// Xóa node tại vị trí cụ thể
void erase(doubly_List **head, int vitri) {
    if (vitri < 0 || vitri >= size_DouList(*head)) {
        printf("Vi tri khong hop le!\n");
        return;
    }
    if (vitri == 0) {
        pop_front(head);
        return;
    }
    doubly_List *temp = *head;
    for (int i = 0; i < vitri; i++) {
        temp = temp->next;
    }
    temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    free(temp);
}

// Lấy giá trị node đầu tiên
int get_Front(doubly_List *head) {
    return empty(head) ? -1 : head->data;
}

// Lấy giá trị node cuối cùng
int get_Back(doubly_List *head) {
    if (empty(head)) return -1;
    while (head->next) head = head->next;
    return head->data;
}

// Lấy giá trị node tại vị trí cụ thể
void get(doubly_List *head, int vitri) {
    if (vitri < 0 || vitri >= size_DouList(head)) {
        printf("Vi tri khong hop le!\n");
        return;
    }
    for (int i = 0; i < vitri; i++) {
        head = head->next;
    }
    printf("Gia tri tai Node[%d] = %d\n", vitri, head->data);
}
