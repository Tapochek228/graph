#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    char *data;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

Stack *init();
void push(Stack *stack, const char *data);
char *pop(Stack *stack);
char *peek(Stack *stack);
int is_empty(Stack *stack);
void destroy(Stack *stack);

#endif