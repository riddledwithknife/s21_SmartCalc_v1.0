#include "finance_calc.h"

// CreditCalc
void calculate_credit(CreditInputData CreditInputDataS, CreditInfo *CreditInfoS,
                      int credit_type) {
  CreditInputDataS.term *= 12;

  if (credit_type == ANNUITY) {
    calculate_annuity(CreditInputDataS, CreditInfoS);
  } else if (credit_type == DIFFERENTIATED) {
    calculate_diff(CreditInputDataS, CreditInfoS);
  }
}

void calculate_annuity(CreditInputData CreditInputDataS,
                       CreditInfo *CreditInfoS) {
  double month_payment, coefficient, i;

  i = CreditInputDataS.rate / 12.0 / 100.0;
  coefficient = i * pow(1 + i, CreditInputDataS.term) /
                ((pow(1 + i, CreditInputDataS.term) - 1));
  month_payment = coefficient * CreditInputDataS.amount;

  CreditInfoS->monthly_payment = round_two_digits(month_payment);
  CreditInfoS->overpayment = round_two_digits(
      month_payment * CreditInputDataS.term - CreditInputDataS.amount);
  CreditInfoS->total_payment =
      round_two_digits(month_payment * CreditInputDataS.term);
}

void calculate_diff(CreditInputData CreditInputDataS, CreditInfo *CreditInfoS) {
  double all_payments;
  double term_remains = CreditInputDataS.amount;
  double average_payment = 0;

  for (int i = 0; i < CreditInputDataS.term; i++) {
    all_payments = CreditInputDataS.amount / CreditInputDataS.term +
                   term_remains * CreditInputDataS.rate / 100.0 / 12.0;
    average_payment += all_payments;
    term_remains =
        term_remains - CreditInputDataS.amount / CreditInputDataS.term;
  }

  CreditInfoS->monthly_payment =
      round_two_digits(average_payment / CreditInputDataS.term);
  CreditInfoS->overpayment =
      round_two_digits(average_payment - CreditInputDataS.amount);
  CreditInfoS->total_payment = round_two_digits(average_payment);
}

double round_two_digits(double value) { return round(value * 100.0) / 100.0; }

// DepositCalc
void calculate_deposit_simple(DepositInputData DepositInputDataS,
                              DepositInfo *DepositInfoS) {
  DepositInputDataS.term *= 12;
  double rate_per_month = DepositInputDataS.rate / 12.0 / 100.0;
  double accrued_interest =
      DepositInputDataS.amount * rate_per_month * DepositInputDataS.term;
  double tax = 75000;

  if (accrued_interest > tax) {
    tax = (accrued_interest - tax) * (DepositInputDataS.tax_rate / 100.0);
  } else {
    tax = 0;
  }

  DepositInfoS->accured_interest = round_two_digits(accrued_interest - tax);
  DepositInfoS->tax_amount = round_two_digits(tax);
  DepositInfoS->amount_by_the_end = round_two_digits(DepositInputDataS.amount);
}

void calculate_deposit_capitalization(DepositInputData DepositInputDataS,
                                      DepositInfo *DepositInfoS) {
  DepositInputDataS.term *= 12;
  double rate_per_year = DepositInputDataS.rate / 100.0;
  double result_amount;
  double accrued_interest;
  double tax = 75000;
  int times = DepositInputDataS.frequency;

  DepositInputDataS.frequency =
      (int)floor(DepositInputDataS.frequency * DepositInputDataS.term / 12.0);

  result_amount = DepositInputDataS.amount *
                  pow(1 + (rate_per_year / times), DepositInputDataS.frequency);
  accrued_interest = result_amount - DepositInputDataS.amount;

  if (accrued_interest > tax) {
    tax = (accrued_interest - tax) * (DepositInputDataS.tax_rate / 100.0);
  } else {
    tax = 0;
  }

  DepositInfoS->accured_interest = round_two_digits(accrued_interest - tax);
  DepositInfoS->tax_amount = round_two_digits(tax);
  DepositInfoS->amount_by_the_end = round_two_digits(result_amount);
}
