#include <stdio.h>
#include <stdlib.h>

#include "calculate.h"
#include "parse.h"
#include "stack.h"

int main() {
    printf("\033[0d\033[2J");
    printf("Enter expression:\n");
    int size;
    char *expression = input_string();
    if (expression  !=  NULL)  {
        char **infix = split_expression(expression, &size);
        if (infix !=  NULL)  {
            int postfix_size;
            char **postfix = infix_to_postfix(infix, size, &postfix_size);
            drow(postfix, postfix_size);
            for (int i = 0; i < size; i++) {
                free(infix[i]);
            }
            free(infix);
            for (int i = 0; i < postfix_size; i++) {
                free(postfix[i]);
            }
            free(postfix);
        }
    }
    else {
        printf("\033[0d\033[2J");
        printf("Invalid expression!\n");
    }
    free(expression);
    return 0;
}