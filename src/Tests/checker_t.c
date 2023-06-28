#include "../Model/checker.h"
#include "tests.h"

START_TEST(checker_normal_behavior) {
  {
    int flag;

    const char string[BUFFSIZE] = "5+5-3";
    flag = is_correct(string);

    ck_assert_int_eq(flag, OK);
  }
}
END_TEST

START_TEST(checker_check_len_err) {
  //>255
  {
    int flag;

    const char string[BUFFSIZE];

    for (int i = 0; i < 256; i++) {
      strcat((char *)string, "1");
    }

    flag = check_len(string);

    ck_assert_int_eq(flag, ERROR);
  }
}

START_TEST(checker_check_alphabet_err) {
  // Wrong symbol
  {
    int flag;

    const char string[BUFFSIZE] = "§";
    flag = check_alphabet(string);

    ck_assert_int_eq(flag, ERROR);
  }
}

START_TEST(checker_check_brace_err) {
  // Wrong braces
  {
    int flag;

    const char string[BUFFSIZE] = ")5+3(";
    flag = check_brace(string);

    ck_assert_int_eq(flag, ERROR);
  }

  {
    int flag;

    const char string[BUFFSIZE] = "(.";
    flag = check_brace(string);

    ck_assert_int_eq(flag, ERROR);
  }

  {
    int flag;

    const char string[BUFFSIZE] = ".)";
    flag = check_brace(string);

    ck_assert_int_eq(flag, ERROR);
  }
}

START_TEST(checker_check_signs_err) {
  // Wrong signs
  {
    int flag;

    const char string[BUFFSIZE] = "+*";
    flag = check_signs(string);

    ck_assert_int_eq(flag, ERROR);
  }
}

START_TEST(checker_check_func_err) {
  // Wrong func call
  {
    int flag;

    const char string[BUFFSIZE] = "foo()";
    flag = check_func(string);

    ck_assert_int_eq(flag, ERROR);
  }

  {
    int flag;

    const char string[BUFFSIZE] = "sssssss(x)";
    flag = check_func(string);

    ck_assert_int_eq(flag, ERROR);
  }

  // Good func call
  {
    int flag;

    const char string[BUFFSIZE] = "sin(x)";
    flag = check_func(string);

    ck_assert_int_eq(flag, OK);
  }
}

START_TEST(checker_check_digit_err) {
  // Wrong digits
  {
    int flag;

    const char string[BUFFSIZE] = "5x";
    flag = check_digits(string);

    ck_assert_int_eq(flag, ERROR);
  }

  {
    int flag;

    const char string[BUFFSIZE] = "x5";
    flag = check_digits(string);

    ck_assert_int_eq(flag, ERROR);
  }

  // Double two or more dots
  {
    int flag;

    const char string[BUFFSIZE] = "5..3";
    flag = check_digits(string);

    ck_assert_int_eq(flag, ERROR);
  }

  {
    int flag;

    const char string[BUFFSIZE] = "5.3.4";
    flag = check_digits(string);

    ck_assert_int_eq(flag, ERROR);
  }
}

START_TEST(checker_check_delete_spaces_normal) {
  // Delete spaces
  {
    const char string[BUFFSIZE] = "5 + 5 - 3";
    char output[BUFFSIZE] = {};
    delete_spaces(string, output);

    ck_assert_str_eq(output, "5+5-3");
  }

  // Unary minus
  {
    const char string[BUFFSIZE] = "-5 + 3";
    char output[BUFFSIZE] = {};
    delete_spaces(string, output);

    ck_assert_str_eq(output, "~5+3");
  }

  {
    const char string[BUFFSIZE] = "3+(-5)";
    char output[BUFFSIZE] = {};
    delete_spaces(string, output);

    ck_assert_str_eq(output, "3+(~5)");
  }

  // Unary plus
  {
    const char string[BUFFSIZE] = "+5 + 3";
    char output[BUFFSIZE] = {};
    delete_spaces(string, output);

    ck_assert_str_eq(output, "5+3");
  }

  {
    const char string[BUFFSIZE] = "3+(+5)";
    char output[BUFFSIZE] = {};
    delete_spaces(string, output);

    ck_assert_str_eq(output, "3+(5)");
  }
}

Suite *checker_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("checker_suite");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, checker_normal_behavior);
  tcase_add_test(tc_core, checker_check_len_err);
  tcase_add_test(tc_core, checker_check_alphabet_err);
  tcase_add_test(tc_core, checker_check_brace_err);
  tcase_add_test(tc_core, checker_check_signs_err);
  tcase_add_test(tc_core, checker_check_func_err);
  tcase_add_test(tc_core, checker_check_digit_err);
  tcase_add_test(tc_core, checker_check_delete_spaces_normal);
  suite_add_tcase(s, tc_core);

  return s;
}

int checker_t() {
  int not_failed = 0;
  Suite *s;
  SRunner *sr;

  s = checker_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  not_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return not_failed;
}