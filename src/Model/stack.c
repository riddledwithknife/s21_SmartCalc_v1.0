#include "stack.h"

stack_ch *create_node_ch(char data) {
  stack_ch *node = calloc(1, sizeof(stack_ch));
  node->data = data;
  node->prev = NULL;
  return node;
}

stack_dbl *create_node_dbl(double data) {
  stack_dbl *node = calloc(1, sizeof(stack_dbl));
  node->data = data;
  node->prev = NULL;
  return node;
}

void push_ch(stack_ch **stack, char data) {
  stack_ch *new_node = create_node_ch(data);
  new_node->prev = *stack;
  *stack = new_node;
}

void push_dbl(stack_dbl **stack, double data) {
  stack_dbl *new_node = create_node_dbl(data);
  new_node->prev = *stack;
  *stack = new_node;
}

char pop_ch(stack_ch **stack) {
  stack_ch *temp = *stack;
  char ch = temp->data;
  *stack = temp->prev;
  free(temp);
  return ch;
}

double pop_dbl(stack_dbl **stack) {
  stack_dbl *temp = *stack;
  double number = temp->data;
  *stack = temp->prev;
  free(temp);
  return number;
}
