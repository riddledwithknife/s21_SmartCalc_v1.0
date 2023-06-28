#include "tests.h"

int main() {
  int no_failed = 0;

  no_failed |= checker_t();
  no_failed |= finance_calc_t();
  no_failed |= polish_t();

  return (no_failed == 0) ? 0 : 1;
}