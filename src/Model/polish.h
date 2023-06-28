#ifndef SRC_POLISH_H
#define SRC_POLISH_H

#include <math.h>
#include <string.h>

#include "checker.h"

enum functions {
  s21_cos = 'c',
  s21_sin = 's',
  s21_sqrt = 'q',
  s21_tan = 't',
  s21_acos = 'C',
  s21_asin = 'S',
  s21_atan = 'T',
  s21_ln = 'l',
  s21_log = 'L'
};

double process(char *infix, double x, int *flag);
int get_priority(char ch);
int to_postfix(char *infix, char *postfix);
int is_digit(char ch);
int is_operator(char ch);
int is_func(char ch);
char get_func_name(char ch1, char ch2);
int get_func_len(char func);
void set_space(char *postfix, int *px_idx);
double calculate(char *postfix, double x, int *flag);
double arithmetic_sign(char sign, double num1, double num2, int *flag);
double arithmetic_func(char func, double num, int *flag);

#endif  // SRC_POLISH_H
