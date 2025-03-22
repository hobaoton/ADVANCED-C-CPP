#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "..\\Header\\single_List.h"

// Tạo một Node mới với giá trị data
Node *create_Node(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Khong the cap phat bo nho cho node moi!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Thêm một Node vào cuối danh sách
void push_back(Node **head, int data) {
    Node *new_Node = create_Node(data);
    if (*head == NULL) {
        printf("Cau truc danh sach rong!\n");
        *head = new_Node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_Node;
    }
}

// Đếm số Node trong danh sách
int count_List(Node *head) {
    if (head == NULL) {
        printf("Cau truc danh sach rong!\n");
        return 0;
    } else {
        int count = 0;
        while (head != NULL) {
            count++;
            head = head->next;
        }
        return count;
    }
}

// Xóa Node cuối danh sách
void pop_back(Node **head) {
    if (*head == NULL) return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node *temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Thêm Node vào đầu danh sách
void push_front(Node **head, int data) {
    Node *new_Node = create_Node(data);
    new_Node->next = *head;
    *head = new_Node;
}

// Xóa Node đầu danh sách
void pop_front(Node **head) {
    if (*head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Hiển thị toàn bộ danh sách
void display(Node *head) {
    int i = 0;
    while (head != NULL) {
        printf("Node[%d] = %d\n", i, head->data);
        head = head->next;
        i++;
    }
}

// Chèn Node vào vị trí cho trước
void insert(Node **head, int data, int pos) {
    if (pos == 0) {
        push_front(head, data);
        return;
    }
    if (pos > count_List(*head)) {
        printf("Vi tri %d them vao khong co trong danh sach\n", pos);
        return;
    }
    Node *new_Node = create_Node(data);
    Node *p = *head;
    int index = 0;
    while (p != NULL && index != pos - 1) {
        index++;
        p = p->next;
    }
    if (p == NULL) return;
    new_Node->next = p->next;
    p->next = new_Node;
}

// Xóa Node tại vị trí cho trước
void erase(Node **head, int pos) {
    int count = count_List(*head);
    if (*head == NULL || pos < 0 || pos >= count) {
        printf("Vi tri %d de xoa khong co trong danh sach\n", pos);
        return;
    }
    if (pos == 0) {
        pop_front(head);
        return;
    }
    Node *p = *head;
    int index = 0;
    while (p != NULL && index != pos - 1) {
        index++;
        p = p->next;
    }
    if (p == NULL || p->next == NULL)
        return;
    Node *toDelete = p->next;
    p->next = p->next->next;
    free(toDelete);
}

#define EMPTY -1

// Lấy giá trị Node đầu danh sách
int front(Node *head) {
    if (head == NULL) {
        printf("Danh sach rong! Khong co gia tri\n");
        return EMPTY;
    } else {
        return head->data;
    }
}

// Lấy giá trị Node cuối danh sách
int back(Node *head) {
    if (head == NULL) {
        printf("Danh sach rong! Khong co gia tri\n");
        return EMPTY;
    }
    while (head->next != NULL) {
        head = head->next;
    }
    return head->data;
}

// Lấy và in giá trị của Node tại vị trí pos
void get(Node *head, int pos) {
    int total = count_List(head);
    if (head == NULL || pos < 0 || pos >= total) {
        printf("Khong ton tai vi tri cua Node can tim!\n");
        return;
    }
    int count = 0;
    while (head != NULL && count != pos) {
        head = head->next;
        count++;
    }
    if (head != NULL) {
        printf("Gia tri tai Node[%d] = %d\n", pos, head->data);
    }
}

// Kiểm tra danh sách có rỗng hay không
bool empty(Node *head) {
    return head == NULL;
}

// Xóa toàn bộ danh sách
void clear(Node **head) {
    while (*head != NULL) {
        Node *p = *head;
        *head = (*head)->next;
        free(p);
    }
}
