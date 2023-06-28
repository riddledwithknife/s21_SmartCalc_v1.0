#include "checker.h"

int is_correct(const char *string) {
  int flag = OK;

  flag &= check_len(string);
  flag &= check_alphabet(string);
  flag &= check_brace(string);
  flag &= check_signs(string);
  flag &= check_func(string);
  flag &= check_digits(string);

  return flag;
}

void delete_spaces(const char *string, char *output) {
  char buffer[BUFFSIZE] = {0};

  for (int i = 0, j = 0; string[i] != '\0' && j < BUFFSIZE; i++) {
    if (string[i] != ' ') {
      buffer[j] = string[i];
      j++;
    }
  }

  int i = 0, j = 0;

  if (buffer[0] == '-') {
    output[0] = '~';
    i++, j++;
  } else if (buffer[0] == '+')
    i++;
  else {
    output[j] = buffer[i];
    i++, j++;
  }

  for (; buffer[i] != '\0' && j < BUFFSIZE; i++) {
    if (buffer[i - 1] == '(' && buffer[i] == '-') {
      output[j] = '~';
      j++;
    } else if (buffer[i - 1] == '(' && buffer[i] == '+')
      continue;
    else {
      output[j] = buffer[i];
      j++;
    }
  }
}

int check_len(const char *string) {
  int flag = OK;

  if (strlen(string) > 255 && string != NULL) flag = ERROR;

  return flag;
}

int check_alphabet(const char *string) {
  int flag = OK;
  char *alphabet = " .0123456789()+~-*/^%acgilnoqrstx";

  for (int i = 0; string[i] != '\0'; i++) {
    if (strchr(alphabet, string[i]) == NULL) {
      flag = ERROR;
    }
  }

  return flag;
}

int check_brace(const char *string) {
  int flag = OK;
  int open_brace = 0, close_brace = 0;

  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] == '(') {
      if (i != 0 && strchr(".)0123456789x", string[i - 1])) flag = ERROR;
      if (string[i + 1] != '\0' && strchr(".)+-*/^%", string[i + 1]))
        flag = ERROR;
      open_brace++;
    } else if (string[i] == ')') {
      if (i != 0 && strchr(".(+-*/^%", string[i - 1])) flag = ERROR;
      if (string[i + 1] != '\0' && strchr(".(0123456789xcstal", string[i + 1]))
        flag = ERROR;
      close_brace++;
    }
  }

  if (open_brace != close_brace) flag = ERROR;

  return flag;
}

int check_signs(const char *string) {
  int flag = OK;
  char *signs = "+-*/^%";
  int len = (int)strlen(string);

  for (int i = 0; i < len - 1; i++) {
    if (strchr(signs, string[i]) && strchr("+-*/^%)", string[i + 1])) {
      flag = ERROR;
    }
  }

  return flag;
}

int check_func(const char *string) {
  int flag = OK;
  char str_copy[BUFFSIZE] = {0};
  memcpy(str_copy, string, BUFFSIZE - 1);
  char *funcs[9] = {"cos(",  "sin(",  "tan(", "acos(", "asin(",
                    "atan(", "sqrt(", "ln(",  "log("};

  char func_name[10] = {0};
  int func_idx = 0;

  for (int i = 0; str_copy[i] != '\0' && flag == OK; i++) {
    while (strchr("acgilnoqrst", str_copy[i]) || str_copy[i] == '(') {
      if (func_idx >= 6) {
        flag = ERROR;
        break;
      }
      func_name[func_idx] = str_copy[i];
      if (func_name[func_idx] == '(') break;
      func_idx++;
      i++;
    }

    if (func_name[0] != '\0' && func_name[0] != '(') {
      for (int f = 0; f < 9 && func_name[0] != '\0'; f++) {
        flag = ERROR;
        if (strcmp(func_name, funcs[f]) == 0) {
          flag = OK;
          break;
        }
      }
    }

    memset(func_name, 0, 10);
    func_idx = 0;
  }

  return flag;
}

int check_digits(const char *string) {
  int flag = OK;

  for (int i = 0; string[i] != '\0'; i++) {
    if (is_digit(string[i])) {
      if (i != 0 && strchr(")x", string[i - 1])) flag = ERROR;
      if (string[i + 1] != '\0' && strchr("(xcstal", string[i + 1]))
        flag = ERROR;
    } else if (string[i] == 'x') {
      if (i != 0 && strchr("x)0123456789", string[i - 1])) flag = ERROR;
      if (string[i + 1] != '\0' && strchr("(0123456789cstal", string[i + 1]))
        flag = ERROR;
    }
  }

  for (int i = 0, dot_counter = 0; string[i] != '\0'; i++) {
    if (string[i] == '.') dot_counter++;
    if (dot_counter > 1) flag = ERROR;
    if (!is_digit(string[i]) && string[i] != '.') dot_counter = 0;
  }

  return flag;
}

int is_digit(char ch) {
  int result = 0;

  if (ch >= '0' && ch <= '9') result = 1;

  return result;
}