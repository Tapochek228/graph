#ifndef CALCULATE_H
#define CALCULATE_H

int is_digit_str(const char *str);
double calculate(char **postfix, int size, double Xinit);
void drow(char **postfix, int postfix_size);
#endif