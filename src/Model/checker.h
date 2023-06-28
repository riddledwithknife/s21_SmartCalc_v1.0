#ifndef SRC_CHECKER_H
#define SRC_CHECKER_H

#include <string.h>

#define BUFFSIZE 512

enum flags {
  OK = 1,
  ERROR = 0,
  FORMAT_ERROR = -1,
  CONVERSION_ERROR = -2,
  ARITHMETIC_ERROR = -3
};

void delete_spaces(const char *string, char *output);
int is_correct(const char *string);
int check_len(const char *string);
int check_alphabet(const char *string);
int check_brace(const char *string);
int check_signs(const char *string);
int check_func(const char *string);
int check_digits(const char *string);
int is_digit(char ch);

#endif  // SRC_CHECKER_H
