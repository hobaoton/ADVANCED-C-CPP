#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Định nghĩa cấu trúc danh sách liên kết đôi
typedef struct doubly_List {
    int data;
    struct doubly_List *next;
    struct doubly_List *prev;
} doubly_List;

// Các hàm xử lý danh sách liên kết đôi
bool empty(doubly_List *head);
int size_DouList(doubly_List *head);
doubly_List *create_DouList(int data);

void display_FronttoBack(doubly_List *head);
void display_BacktoFront(doubly_List *head);

void push_front(doubly_List **head, int data);
void push_back(doubly_List **head, int data);
void pop_front(doubly_List **head);
void pop_back(doubly_List **head);

void insert(doubly_List **head, int data, int vitri);
void erase(doubly_List **head, int vitri);

int get_Front(doubly_List *head);
int get_Back(doubly_List *head);
void get(doubly_List *head, int vitri);

#endif
