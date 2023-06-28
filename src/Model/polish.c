#include "polish.h"

#include "stack.h"

double process(char *infix, double x, int *flag) {
  *flag = OK;
  char postfix[BUFFSIZE] = {0};
  char buffer[BUFFSIZE] = {0};
  double result = 0;

  delete_spaces(infix, buffer);

  if (is_correct(buffer) == ERROR) {
    *flag = FORMAT_ERROR;
  }
  if (*flag == OK) {
    strcat(buffer, "+0");
    *flag = to_postfix(buffer, postfix);
  }
  if (*flag == OK) {
    result = calculate(postfix, x, flag);
  }

  return result;
}

int to_postfix(char *infix, char *postfix) {
  int flag = OK;
  int ix_idx = 0, px_idx = 0;
  char funcs_str[10] = {s21_cos,  s21_sin,  s21_tan, s21_acos, s21_asin,
                        s21_atan, s21_sqrt, s21_ln,  s21_log,  '\0'};

  stack_ch *stack1 = NULL;

  while (infix[ix_idx] != '\0' && flag == OK) {
    if (is_digit(infix[ix_idx])) {
      while (is_digit(infix[ix_idx]) || infix[ix_idx] == '.') {
        postfix[px_idx] = infix[ix_idx];
        px_idx++, ix_idx++;
      }
      set_space(postfix, &px_idx);
    } else if (infix[ix_idx] == 'x') {
      postfix[px_idx] = infix[ix_idx];
      px_idx++, ix_idx++;
      set_space(postfix, &px_idx);
    } else if (is_func(infix[ix_idx])) {
      char func_name = get_func_name(infix[ix_idx], infix[ix_idx + 1]);

      push_ch(&stack1, func_name);
      ix_idx += get_func_len(func_name);
    } else if (infix[ix_idx] == '(') {
      push_ch(&stack1, '(');
      ix_idx++;
    } else if (is_operator(infix[ix_idx]) || infix[ix_idx] == '~') {
      int priority1 = -1, priority2 = -1;
      char op_stack = '\0';

      while (stack1 != NULL) {
        op_stack = pop_ch(&stack1);
        priority1 = get_priority(infix[ix_idx]);
        priority2 = get_priority(op_stack);
        if (strchr(funcs_str, op_stack) || priority2 >= priority1) {
          postfix[px_idx] = op_stack;
          px_idx++;
          set_space(postfix, &px_idx);
        } else {
          push_ch(&stack1, op_stack);
          break;
        }
      }
      push_ch(&stack1, infix[ix_idx]);
      ix_idx++;
    }

    else if (infix[ix_idx] == ')') {
      flag = ERROR;
      while (stack1 != NULL) {
        if (stack1->data != '(') {
          flag = OK;
          postfix[px_idx] = pop_ch(&stack1);
          px_idx++;
          set_space(postfix, &px_idx);
        } else {
          pop_ch(&stack1);
          flag = OK;
          break;
        }
      }
      ix_idx++;
    } else {
      flag = ERROR;
    }
  }

  while (stack1 != NULL && flag == OK) {
    if (stack1->data == '(' || stack1->data == ')') flag = ERROR;

    postfix[px_idx] = pop_ch(&stack1);
    px_idx++;
    set_space(postfix, &px_idx);
  }

  if (flag == ERROR) {
    memset(postfix, 0, 1024);
    flag = CONVERSION_ERROR;
  }

  return flag;
}

int get_priority(char ch) {
  int priority = -1;

  if (ch == '(' || ch == ')')
    priority = 0;
  else if (ch == '+' || ch == '-')
    priority = 1;
  else if (ch == '*' || ch == '/' || ch == '%')
    priority = 2;
  else if (ch == '^' || strchr("sctCSTqlL", ch))
    priority = 3;
  else if (ch == '~')
    priority = 4;

  return priority;
}

int is_operator(char ch) {
  int result = 0;

  if (strchr("+-*/%^", ch)) result = 1;

  return result;
}

int is_func(char ch) {
  int result = 0;

  if (strchr("cstal", ch)) result = 1;

  return result;
}

char get_func_name(char ch1, char ch2) {
  char result = 0;

  if (ch1 == '\0' || ch2 == '\0')
    result = -1;
  else if (ch1 == 'c' && ch2 == 'o')
    result = s21_cos;
  else if (ch1 == 's' && ch2 == 'i')
    result = s21_sin;
  else if (ch1 == 't' && ch2 == 'a')
    result = s21_tan;
  else if (ch1 == 'a' && ch2 == 'c')
    result = s21_acos;
  else if (ch1 == 'a' && ch2 == 's')
    result = s21_asin;
  else if (ch1 == 'a' && ch2 == 't')
    result = s21_atan;
  else if (ch1 == 's' && ch2 == 'q')
    result = s21_sqrt;
  else if (ch1 == 'l' && ch2 == 'n')
    result = s21_ln;
  else if (ch1 == 'l' && ch2 == 'o')
    result = s21_log;

  return result;
}

int get_func_len(char func) {
  int result = 0;

  if (func == s21_cos || func == s21_sin || func == s21_tan || func == s21_log)
    result = 3;
  else if (func == s21_acos || func == s21_asin || func == s21_atan ||
           func == s21_sqrt)
    result = 4;
  else if (func == s21_ln)
    result = 2;

  return result;
}

void set_space(char *postfix, int *px_idx) {
  postfix[*px_idx] = ' ';
  (*px_idx)++;
}

double calculate(char *postfix, double x, int *flag) {
  *flag = OK;
  char buffer[256] = {0};
  char *temp = NULL;
  stack_dbl *stack1 = NULL;
  double result = 0, number = 0;
  double num1 = 0, num2 = 0;
  char funcs_str[10] = {s21_cos,  s21_sin,  s21_tan, s21_acos, s21_asin,
                        s21_atan, s21_sqrt, s21_ln,  s21_log,  '\0'};

  for (int i = 0; postfix[i] != '\0' && *flag == OK; i++) {
    if (is_digit(postfix[i])) {
      for (int bf = 0; is_digit(postfix[i]) || postfix[i] == '.'; bf++, i++) {
        buffer[bf] = postfix[i];
      }
      number = strtod(buffer, &temp);
      if (strcmp(buffer, temp) == 0)
        *flag = ARITHMETIC_ERROR;
      else {
        push_dbl(&stack1, number);
        memset(buffer, 0, 256);
      }
    } else if (postfix[i] == 'x') {
      push_dbl(&stack1, x);
    } else if (strchr(funcs_str, postfix[i])) {
      num1 = pop_dbl(&stack1);
      result = arithmetic_func(postfix[i], num1, flag);
      push_dbl(&stack1, result);

    } else if (strchr("+-*/%^~", postfix[i])) {
      if (stack1 != NULL) {
        num2 = pop_dbl(&stack1);
      } else {
        *flag = FORMAT_ERROR;
      }
      if (postfix[i] == '~') {
        num1 = 0;
      } else {
        if (stack1 != NULL) {
          num1 = pop_dbl(&stack1);
        } else {
          *flag = FORMAT_ERROR;
        }
      }
      if (*flag == OK) {
        result = arithmetic_sign(postfix[i], num1, num2, flag);
        push_dbl(&stack1, result);
      }
    }
  }

  while (stack1 != NULL) {
    pop_dbl(&stack1);
  }

  return result;
}

double arithmetic_sign(char sign, double num1, double num2, int *flag) {
  double result = 0;

  if (sign == '+') {
    result = num1 + num2;
  } else if (sign == '-') {
    result = num1 - num2;
  } else if (sign == '*') {
    result = num1 * num2;
  } else if (sign == '/') {
    if (num2 == 0)
      *flag = ARITHMETIC_ERROR;
    else
      result = num1 / num2;
  } else if (sign == '^') {
    result = pow(num1, num2);
  } else if (sign == '%') {
    if (num2 == 0)
      *flag = ARITHMETIC_ERROR;
    else
      result = fmod(num1, num2);
  } else if (sign == '~') {
    result = num1 - num2;
  } else {
    *flag = ARITHMETIC_ERROR;
  }

  return result;
}

double arithmetic_func(char func, double num, int *flag) {
  double result = 0;

  if (func == s21_cos) {
    result = cos(num);
  } else if (func == s21_sin) {
    result = sin(num);
  } else if (func == s21_tan) {
    result = tan(num);
  } else if (func == s21_acos) {
    if (num < -1 || num > 1)
      *flag = ARITHMETIC_ERROR;
    else
      result = acos(num);
  } else if (func == s21_asin) {
    if (num < -1 || num > 1)
      *flag = ARITHMETIC_ERROR;
    else
      result = asin(num);
  } else if (func == s21_atan) {
    result = atan(num);
  } else if (func == s21_sqrt) {
    if (num < 0)
      *flag = ARITHMETIC_ERROR;
    else
      result = sqrt(num);
  } else if (func == s21_ln) {
    if (num <= 0)
      *flag = ARITHMETIC_ERROR;
    else
      result = log(num);
  } else if (func == s21_log) {
    if (num <= 0)
      *flag = ARITHMETIC_ERROR;
    else
      result = log10(num);
  } else {
    *flag = ARITHMETIC_ERROR;
  }

  return result;
}
