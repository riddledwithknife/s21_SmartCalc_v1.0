#include "../Model/finance_calc.h"
#include "tests.h"

// Credit Calc Tests
START_TEST(credit_calc_normal_behavior) {
  // Annuity
  {
    CreditInputData CreditInputDataS = {500000, 2, 12};
    CreditInfo CreditInfoS = {};

    calculate_credit(CreditInputDataS, &CreditInfoS, 1);

    ck_assert_int_eq(CreditInfoS.monthly_payment, 23536);
    ck_assert_int_eq(CreditInfoS.overpayment, 64881);
    ck_assert_int_eq(CreditInfoS.total_payment, 564881);
  }

  // Diff
  {
    CreditInputData CreditInputDataS = {500000, 2, 12};
    CreditInfo CreditInfoS = {};

    calculate_credit(CreditInputDataS, &CreditInfoS, 2);

    ck_assert_int_eq(CreditInfoS.monthly_payment, 23437);
    ck_assert_int_eq(CreditInfoS.overpayment, 62500);
    ck_assert_int_eq(CreditInfoS.total_payment, 562500);
  }
}
END_TEST

// Deposit Calc Tests
START_TEST(deposit_calc_normal_behavior) {
  // No cap
  {
    DepositInputData DepositInputDataS = {500000, 2, 20, 0, 13};
    DepositInfo DepositInfoS = {};

    calculate_deposit_simple(DepositInputDataS, &DepositInfoS);

    ck_assert_int_eq(DepositInfoS.accured_interest, 183750);
    ck_assert_int_eq(DepositInfoS.tax_amount, 16250);
    ck_assert_int_eq(DepositInfoS.amount_by_the_end, 500000);
  }

  // Cap
  {
    DepositInputData DepositInputDataS = {500000, 2, 20, 1, 13};
    DepositInfo DepositInfoS = {};

    calculate_deposit_capitalization(DepositInputDataS, &DepositInfoS);

    ck_assert_int_eq(DepositInfoS.accured_interest, 201150);
    ck_assert_int_eq(DepositInfoS.tax_amount, 18850);
    ck_assert_int_eq(DepositInfoS.amount_by_the_end, 720000);
  }
}
END_TEST

Suite *finance_calc_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("finance_calc_suite");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, credit_calc_normal_behavior);
  tcase_add_test(tc_core, deposit_calc_normal_behavior);
  suite_add_tcase(s, tc_core);

  return s;
}

int finance_calc_t() {
  int not_failed = 0;
  Suite *s;
  SRunner *sr;

  s = finance_calc_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  not_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return not_failed;
}