#ifndef SRC_STACK_H
#define SRC_STACK_H

#include <stdlib.h>

typedef struct stack_ch {
  char data;
  struct stack_ch *prev;
} stack_ch;

typedef struct stack_dbl {
  double data;
  struct stack_dbl *prev;
} stack_dbl;

stack_ch *create_node_ch(char data);
stack_dbl *create_node_dbl(double data);

void push_ch(stack_ch **stack, char data);
void push_dbl(stack_dbl **stack, double data);

char pop_ch(stack_ch **stack);
double pop_dbl(stack_dbl **stack);

#endif  // SRC_STACK_H
