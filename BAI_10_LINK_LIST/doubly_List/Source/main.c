#include "..\\Header\\doubly_List.h"

int main() {
    doubly_List *head = NULL;

    push_front(&head, 10);
    push_front(&head, 20);
    push_back(&head, 30);
    push_back(&head, 40);

    display_FronttoBack(head);
    printf("\n");

    pop_front(&head);
    pop_back(&head);

    display_FronttoBack(head);
    printf("\n");

    insert(&head, 25, 1);
    display_FronttoBack(head);

    return 0;
}
