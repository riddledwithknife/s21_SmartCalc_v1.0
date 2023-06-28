#include "../Model/polish.h"
#include "tests.h"

START_TEST(polish_normal_behavior) {
  {
    char infix[BUFFSIZE] = "sqrt(-x+30)";
    double x = 5;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, 5, 1e-6);
  }

  {
    char infix[BUFFSIZE] = "sin(x*5)";
    double x = 5;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, sin(x * 5), 1e-6);
  }

  {
    char infix[BUFFSIZE] = "cos(x/5)";
    double x = 5;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, cos(x / 5), 1e-6);
  }

  {
    char infix[BUFFSIZE] = "tan(x%5)";
    double x = 5;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, tan(0), 1e-6);
  }

  {
    char infix[BUFFSIZE] = "atan(x - 1)";
    double x = 1.5;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, atan(x - 1), 1e-6);
  }

  {
    char infix[BUFFSIZE] = "asin(x ^ 5)";
    double x = 0;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, asin(0), 1e-6);
  }

  {
    char infix[BUFFSIZE] = "acos(x)";
    double x = 0.5;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, acos(x), 1e-6);
  }

  {
    char infix[BUFFSIZE] = "log(x)";
    double x = 1;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, log10(x), 1e-6);
  }

  {
    char infix[BUFFSIZE] = "ln(x)";
    double x = 1;
    int flag;

    double result = process(infix, x, &flag);

    ck_assert_double_eq_tol(result, log(x), 1e-6);
  }
}
END_TEST

Suite *polish_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("polish_suite");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, polish_normal_behavior);
  suite_add_tcase(s, tc_core);

  return s;
}

int polish_t() {
  int not_failed = 0;
  Suite *s;
  SRunner *sr;

  s = polish_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  not_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return not_failed;
}