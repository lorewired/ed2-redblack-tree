#ifndef STACK_H
#define STACK_H

#include "utils.h"

typedef struct _stack_node {
    void* value;
    struct _stack_node* prev;
} stack_node;

stack_node* new_stack_node(void* value);

typedef struct {
    uint32_t size;
    stack_node* top;
} stack;

stack new_stack();

void* stack_top(stack* stk);

uint32_t stack_size(stack* stk);

bool stack_empty(stack* stk);

void stack_push(stack* stk, void* value);

void* stack_pop(stack* stk);

#endif