#include <stdlib.h>

#include "linkedlist/list.h"
#include "stack.h"

int stack_push(Stack *stack, const void *data)
{
    // Push data onto the stack
    return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data)
{
    // Pop the data off the stack
    return list_rem_next(stack, NULL, data);
}


