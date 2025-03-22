#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*==============================================================================
**  Dự án  : MyAutosarProject
**  Module : Stack
**  File   : Stack.c
**  Mô tả  : Định nghĩa các hàm cho module Stack theo nội dung ban đầu,
**           không bao gồm hàm main.
==============================================================================*/

void init_Stack (Stack *stack, int size)
{
    stack->item = (int*)malloc(size * sizeof(int));
    stack->size = size;
    stack->top = -1;
}

bool empty_Stack (Stack stack)
{
    if (stack.top == -1 )
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool full_Stack (Stack stack)
{
    if (stack.top == stack.size - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void push_Stack (Stack *stack, int data)
{
    if (full_Stack(*stack))
    {
        printf ("Stack day!\n");
        return;
    }
    stack->item[++stack->top] = data;
}

void pop_Stack (Stack *stack)
{
    if (empty_Stack(*stack))
    {
        printf ("Stack rong!\n");
        return;
    }
    
    int i = stack->top, a = stack->item[stack->top];
    stack->item[stack->top] = 0;
    stack->top--;
    printf("Dinh %d gia tri %d da thu hoi!\n", i, a);
}

int get_Stack (Stack stack)
{
    if (empty_Stack(stack))
    {  
        printf ("Stack rong!\n"); 
        return -1;
    }
    else
    {
        return stack.item[stack.top];
    }
}

void display_Stack (Stack stack)
{
    for (int i = 0; i < stack.top; i++)
    {
        printf ("Vi tri %d gia tri %d\n", i, stack.item[i]);
    }
}
