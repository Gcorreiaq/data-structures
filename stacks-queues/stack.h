#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "../linked-lists/list.h"

typedef List Stack;

// since a stack is a linked list, stack_init is defined to list_init
#define stack_init list_init

#define stack_destroy list_destroy

// the stack_push pushes an element onto the top of a stack by calling list_ins_next to insert an element pointing to data at the head of the list
int stack_push(Stack *stack, const void *data);

// the stack_pop pops an element off the top of a stack by calling list_rem_next to remove the element at the head of the list
int stack_pop(Stack *stack, void **data);

#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

#define stack_size list_size

int stack_push(Stack *stack, const void *data) {
    return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data) {
    return list_rem_next(stack, NULL, data);
}

#endif
