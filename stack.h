#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "linkedlist/list.h"

// Implements stack as linked list
typedef List Stack;


// Public interface

#define stack_init list_init

#define stack_destory list_destroy

int stack_push(Stack *stack, void **data);

int stack_pop(Stack *stack, void **data);

#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

#define stack_size list_size


#endif