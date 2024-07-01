#ifndef PARSE_H
#define PARSE_H

char **split_expression(char *expression, int *size);
int is_operator(char c);
int is_digit(char c);
char *input_string();
char **add_string_to_array(char **array, int *size, char *string_to_add);
void output(char **array, int n);
char **infix_to_postfix(char **infix, int size, int *postfix_size);
int precedence(char *operator_);
int is_function(char *token);
int find_symbol(char symbol, char* string);
#endif