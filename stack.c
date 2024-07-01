#include "stack.h"

#include <stdlib.h>
#include <string.h>

Stack *init() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, const char *data) {
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = strdup(data);
    node->next = stack->top;
    stack->top = node;
}

char *pop(Stack *stack) {
    if (is_empty(stack)) {
        return NULL;
    }
    StackNode *node = stack->top;
    stack->top = node->next;
    char *data = node->data;
    free(node);
    return data;
}

char *peek(Stack *stack) {
    if (is_empty(stack)) {
        return NULL;
    }
    return stack->top->data;
}

int is_empty(Stack *stack) { return stack->top == NULL; }

void destroy(Stack *stack) {
    while (!is_empty(stack)) {
        char *data = pop(stack);
        free(data);
    }
    free(stack);
}