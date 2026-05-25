#include "stack.h"

#pragma region STACK_NODE
stack_node* new_stack_node(void* value) {
    stack_node* node = malloc(sizeof(stack_node));
    if (node) node->value = value;
    return node;
}
#pragma endregion

#pragma region STACK
stack new_stack() {
    return (stack) {
        .size = 0,
        .top  = NULL
    };
}

void* stack_top(stack stk) {
    return stk.top->value;
}

uint32_t stack_size(stack stk) {
    return stk.size;
}

bool stack_empty(stack stk) {
    return ! stk.size;
}

void stack_push(stack* stk, void* value) {
    stack_node* node = new_stack_node(value);
    if (!node) return;
    node->prev = stk->top;
    stk->top = node;
    stk->size++;
}

void stack_pop(stack* stk) {
    if (!stk->size) return;
    stack_node* rm = stk->top;
    stk->top = rm->prev;
    free(rm);
    stk->size--;
}
#pragma endregion