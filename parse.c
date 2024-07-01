#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

char **split_expression(char *expression, int *size) {
    char **result = NULL;
    *size = 0;
    char *start = NULL, *number = NULL;

    while (*expression) {
        if (is_digit(*expression)) {
            start = expression;
            while (is_digit(*expression)) {
                expression++;
            }
            number = strndup(start, expression - start);
            result = add_string_to_array(result, size, number);
            free(number);
        } else if (is_operator(*expression)) {
            if (*expression == '-' && (*(expression - 1) == '(')) {
                char only_null[2] = {'0', '\0'};
                result = add_string_to_array(result, size, only_null);
            }
            char operator[2] = {*expression, '\0'};
            result = add_string_to_array(result, size, operator);
            expression++;
        } else {
            if (*expression == 's' && *(expression + 1) == 'i' && *(expression + 2) == 'n') {
                result = add_string_to_array(result, size, "sin");
                expression += 3;
            } else if (*expression == 'c' && *(expression + 1) == 'o' && *(expression + 2) == 's') {
                result = add_string_to_array(result, size, "cos");
                expression += 3;
            } else if (*expression == 't' && *(expression + 1) == 'a' && *(expression + 2) == 'n') {
                result = add_string_to_array(result, size, "tan");
                expression += 3;
            } else if (*expression == 'c' && *(expression + 1) == 't' && *(expression + 2) == 'g') {
                result = add_string_to_array(result, size, "ctg");
                expression += 3;
            } else if (*expression == 's' && *(expression + 1) == 'q' && *(expression + 2) == 'r' && *(expression + 3) == 't') {
                result = add_string_to_array(result, size, "sqrt");
                expression += 4;
            } else if (*expression == 'l' && *(expression + 1) == 'n') {
                result = add_string_to_array(result, size, "ln");
                expression += 2;
            } else {
                for (int  i  =  0;  i  <  *size;  i++)  {
                    free(result[i]);
                }
                free(result);
                free(start);
                free(number);
                return NULL;
            }
        }
    }
    return result;
}

int is_operator(char c) {return c== '-' || c <= '+' || c == '*' || c == '/' || c== '(' || c==')';}

int is_digit(char c) { return ('0' <= c && c <= '9') || c == 'x' || c == '.'; }

char *input_string() {
    char c;
    int n = 2;
    char *string = (char *)malloc(n * sizeof(char));
    string[0] = '(';
    if ((c = getchar()) != '\n') {string[1] = c;}
    else { free(string);return NULL;}
    while ((c = getchar()) != '\n') {
        char *temp = realloc(string, (n + 1) * sizeof(char));
        if (temp == NULL) {
            free(string); 
            return NULL;
        } else {
            string = temp;
        }
        string[n] = c;
        n++;
    }
    string = realloc(string, (n + 2) * sizeof(char)); 
    string[n] = ')';
    string[n + 1] = '\0';
    int flag=0;
    for (int i  =  0; i  <  n; i++)  {
        if(!is_digit(string[i]) && !is_operator(string[i])){
            flag=1;

        }
    }
    if (find_symbol(')',string)!=find_symbol('(', string) && flag!=1){
        free(string);
        return NULL;
    }
    return string;
}

char **add_string_to_array(char **array, int *size, char *string_to_add) {
    char **new_array = realloc(array, (*size + 1) * sizeof(char *));
    if (new_array == NULL) {
        for (int i = 0; i < *size; i++) {
            free(array[i]);
        }
        free(array);
        return NULL;
    }
    array = new_array;
    array[*size] = strdup(string_to_add);
    if (array[*size] == NULL) {
        for (int i = 0; i < *size; i++) {
            free(array[i]);
        }
        free(array);
        return NULL;
    }
    (*size)++;
    return array;
}

char **infix_to_postfix(char **infix, int size, int *postfix_size) {
    Stack *stack = init();
    char **postfix = NULL;
    *postfix_size = 0;
    for (int i = 0; i < size; i++) {
        char *token = infix[i];
        if (is_digit(token[0])) {
            postfix = add_string_to_array(postfix, postfix_size, token);
        } else if (is_function(token)) {
            push(stack, token);
        } else if (strcmp(token, "(") == 0) {
            push(stack, token);
        } else if (strcmp(token, ")") == 0) {
            while (!is_empty(stack) && strcmp(peek(stack), "(") != 0) {
                char *popped = pop(stack);
                postfix = add_string_to_array(postfix, postfix_size, popped);
                free(popped); 
            }
            free(pop(stack)); 
            if (!is_empty(stack) && is_function(peek(stack))) {
                char *popped = pop(stack);
                postfix = add_string_to_array(postfix, postfix_size, popped);
                free(popped); 
            }
        } else if (is_operator(token[0])) {
            while (!is_empty(stack) && strcmp(peek(stack), "(") != 0 &&
                   precedence(peek(stack)) >= precedence(token)) {
                char *popped = pop(stack);
                postfix = add_string_to_array(postfix, postfix_size, popped);
                free(popped);
            }
            push(stack, token);
        }
    }
    while (!is_empty(stack)) {
        char *popped = pop(stack);
        postfix = add_string_to_array(postfix, postfix_size, popped);
        free(popped);
    }
    destroy(stack);
    return postfix;
}

int precedence(char *operator_) {
    if (strcmp(operator_, "+") == 0 || strcmp(operator_, "-") == 0) {
        return 1;
    } else if (strcmp(operator_, "*") == 0 || strcmp(operator_, "/") == 0) {
        return 2;
    } else if (is_function(operator_)) {
        return 3;
    }
    return 0;
}

int is_function(char *token) {
    return strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0 ||
           strcmp(token, "ctg") == 0 || strcmp(token, "sqrt") == 0 || strcmp(token, "ln") == 0;
}

int find_symbol(char symbol, char* string) {
    int flag=0;
    int length = strlen(string);
    for (int i =0;  i < length; i++) {
        if (string[i] == symbol) {
            flag++;
        }
    }
    return flag;
}