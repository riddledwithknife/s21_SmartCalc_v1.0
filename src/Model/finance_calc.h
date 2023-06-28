#ifndef SRC_FINANCE_CALC_H
#define SRC_FINANCE_CALC_H

#include <math.h>
#include <stdlib.h>

#include "checker.h"

#define ANNUITY 1
#define DIFFERENTIATED 2

enum frequency {
  day = 365,
  week = 52,
  month = 12,
  quarter = 4,
  half_year = 2,
  year = 1
};

typedef struct CreditInputData {
  double amount;
  int term;
  double rate;
} CreditInputData;

typedef struct CreditInfo {
  double monthly_payment;
  double overpayment;
  double total_payment;
} CreditInfo;

typedef struct DepositInputData {
  double amount;
  int term;
  double rate;
  int frequency;
  double tax_rate;
} DepositInputData;

typedef struct DepositInfo {
  double accured_interest;
  double tax_amount;
  double amount_by_the_end;
} DepositInfo;

// CreditCalc
void calculate_credit(CreditInputData CreditInputDataS, CreditInfo *CreditInfoS,
                      int credit_type);
void calculate_annuity(CreditInputData CreditInputDataS,
                       CreditInfo *CreditInfoS);
void calculate_diff(CreditInputData CreditInputDataS, CreditInfo *CreditInfoS);
double round_two_digits(double value);

// DepositCalc
void calculate_deposit_simple(DepositInputData DepositInputDataS,
                              DepositInfo *DepositInfoS);
void calculate_deposit_capitalization(DepositInputData DepositInputDataS,
                                      DepositInfo *DepositInfoS);

#endif  // SRC_FINANCE_CALC_H