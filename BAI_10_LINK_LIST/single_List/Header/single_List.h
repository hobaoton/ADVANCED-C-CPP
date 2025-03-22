#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <stdbool.h>

// Định nghĩa struct cho Node của danh sách liên kết đơn
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Khai báo các hàm thao tác với danh sách liên kết đơn
Node *create_Node(int data);
void push_back(Node **head, int data);
int count_List(Node *head);
void pop_back(Node **head);
void push_front(Node **head, int data);
void pop_front(Node **head);
void display(Node *head);
void insert(Node **head, int data, int pos);
void erase(Node **head, int pos);
int front(Node *head);
int back(Node *head);
void get(Node *head, int pos);
bool empty(Node *head);
void clear(Node **head);

#endif // SINGLE_LIST_H
