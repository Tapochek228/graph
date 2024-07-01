#include "calculate.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "stack.h"
#define HIGHT 25
#define LENGHT 80

double calculate(char **postfix, int size, double Xinit) {
    Stack *stack = init();
    for (int i = 0; i < size; i++) {
        char *token = postfix[i];
        double result = 0;
        if (is_digit(*token)) {
            char result_str[50];
            snprintf(result_str, sizeof(result_str), "%lf", Xinit);
            if (strcmp(token, "x") == 0) {
                push(stack, result_str);
            } else {
                push(stack, token);
            }
        } else if (is_function(token)) {
            double operand = 0;
            char *test3 = pop(stack);
            if (strcmp(test3, "x") == 0) {
                operand = Xinit;
            } else {
                operand = atof(test3);
            }
            free(test3);
            if (strcmp(token, "sin") == 0) {
                result = sin(operand);
            } else if (strcmp(token, "cos") == 0) {
                result = cos(operand);
            } else if (strcmp(token, "tan") == 0) {
                result = sin(operand)/cos(operand);
            } else if (strcmp(token, "ctg") == 0) {
                result =  cos(operand)/sin(operand);
            } else if (strcmp(token, "sqrt") == 0) {
                result = sqrt(operand);
            } else if (strcmp(token, "ln") == 0) {
                result = log(operand);
            } else {
                result = operand;
            }
            char result_str[50];
            snprintf(result_str, sizeof(result_str), "%lf", result);
            push(stack, result_str);
        } else if (is_operator(token[0])) {
            char *test = pop(stack);
            double right_operand = 0;
            double left_operand = 0;
            if (strcmp(test, "x") == 0) {
                right_operand = Xinit;
            } else {
                right_operand = atof(test);
            }
            char *test1 = pop(stack);
            if (strcmp(test1, "x") == 0) {
                left_operand = Xinit;
            } else {
                left_operand = atof(test1);
            }
            free(test);
            free(test1);
            switch (token[0]) {
                case '+':
                    result = left_operand + right_operand;
                    break;
                case '-':
                    result = left_operand - right_operand;
                    break;
                case '*':
                    result = left_operand * right_operand;
                    break;
                case '/':
                    if(right_operand==0){exit(0);}
                    result = left_operand / right_operand;
                    break;
                default:
                    result = Xinit;
                    break;
            }
            char result_str[50];
            snprintf(result_str, sizeof(result_str), "%lf", result);
            push(stack, result_str);
        }
    }
    char *final_result_str = pop(stack);
    double final_result = atof(final_result_str);
    free(final_result_str);
    destroy(stack);
    return final_result;
}

void drow(char **postfix, int postfix_size) {
    double shag_x = 4 * M_PI / 80;
    double shag_y = 2.0 / 25;
    double poz_y = -1.0;
    for (int i = 0; i < 25; i++) {
        double poz_x = 0.0;
        for (int j = 0; j < 80; j++) {
            double ans = calculate(postfix, postfix_size, poz_x);
            if (poz_y <= ans && ans <= poz_y + shag_y+0.001) {
                printf("* ");
            } else {
                printf("  ");
            }
            poz_x += shag_x;
        }
        printf("\n");
        poz_y += shag_y;
    }
}