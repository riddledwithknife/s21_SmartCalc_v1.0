#include "s21_financewindow.h"

s21_FinanceWindow::s21_FinanceWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::s21_FinanceWindow) {
  ui->setupUi(this);
}

s21_FinanceWindow::~s21_FinanceWindow() { delete ui; }

void s21_FinanceWindow::on_CREDITCALCMENU_clicked() {
  if (ui->ModeTab->currentIndex() == 1) {
    QString style = ui->CREDITCALCMENU->styleSheet();
    ui->CREDITCALCMENU->setStyleSheet(ui->DEPOSITCALCMENU->styleSheet());
    ui->DEPOSITCALCMENU->setStyleSheet(style);
    ui->ModeTab->setCurrentIndex(0);
  }
}

void s21_FinanceWindow::on_DEPOSITCALCMENU_clicked() {
  if (ui->ModeTab->currentIndex() == 0) {
    QString style = ui->DEPOSITCALCMENU->styleSheet();
    ui->DEPOSITCALCMENU->setStyleSheet(ui->CREDITCALCMENU->styleSheet());
    ui->CREDITCALCMENU->setStyleSheet(style);
    ui->ModeTab->setCurrentIndex(1);
  }
}

void s21_FinanceWindow::on_Calculate_clicked() {
  CreditInputData CreditInputDataS;
  CreditInfo CreditInfoS;

  CreditInputDataS.amount = ui->DepositAmount->text().toDouble();
  CreditInputDataS.term = ui->Term->text().toInt();
  CreditInputDataS.rate = ui->InterestRate->text().toDouble();

  if (ui->Annuity->isChecked()) {
    int credit_type = 1;

    calculate_credit(CreditInputDataS, &CreditInfoS, credit_type);
  } else if (ui->Differentiated->isChecked()) {
    int credit_type = 2;

    calculate_credit(CreditInputDataS, &CreditInfoS, credit_type);
  }

  ui->MonthlyPayment->setText(
      QString::fromStdString(std::to_string(CreditInfoS.monthly_payment)));
  ui->Overpayment->setText(
      QString::fromStdString(std::to_string(CreditInfoS.overpayment)));
  ui->TotalPayout->setText(
      QString::fromStdString(std::to_string(CreditInfoS.total_payment)));
}

void s21_FinanceWindow::on_Clear_clicked() {
  ui->DepositAmount->setText("");
  ui->Term->setText("");
  ui->InterestRate->setText("");

  ui->MonthlyPayment->setText("");
  ui->Overpayment->setText("");
  ui->TotalPayout->setText("");
}

void s21_FinanceWindow::on_Annuity_clicked() {
  ui->Differentiated->setChecked(false);
}

void s21_FinanceWindow::on_Differentiated_clicked() {
  ui->Annuity->setChecked(false);
}

void s21_FinanceWindow::on_Calculate_2_clicked() {
  DepositInputData DepositInputDataS;
  DepositInfo DepositInfoS;

  DepositInputDataS.amount = ui->DepositAmount_2->text().toDouble();
  DepositInputDataS.term = ui->Term_2->text().toInt();
  DepositInputDataS.rate = ui->InterestRate_2->text().toDouble();
  DepositInputDataS.frequency = ui->Date->currentIndex();
  DepositInputDataS.tax_rate = ui->TaxRate->text().toDouble();

  if (DepositInputDataS.frequency == 1) {
    DepositInputDataS.frequency = day;
  } else if (DepositInputDataS.frequency == 2) {
    DepositInputDataS.frequency = week;
  } else if (DepositInputDataS.frequency == 3) {
    DepositInputDataS.frequency = month;
  } else if (DepositInputDataS.frequency == 4) {
    DepositInputDataS.frequency = quarter;
  } else if (DepositInputDataS.frequency == 5) {
    DepositInputDataS.frequency = half_year;
  } else if (DepositInputDataS.frequency == 6) {
    DepositInputDataS.frequency = year;
  }

  if (ui->YesCap->isChecked()) {
    calculate_deposit_capitalization(DepositInputDataS, &DepositInfoS);
  } else if (ui->NoCap->isChecked()) {
    calculate_deposit_simple(DepositInputDataS, &DepositInfoS);
  }

  ui->AccuredInterest->setText(
      QString::fromStdString(std::to_string(DepositInfoS.accured_interest)));
  ui->TaxAmount->setText(
      QString::fromStdString(std::to_string(DepositInfoS.tax_amount)));
  ui->AmountByTheEnd->setText(
      QString::fromStdString(std::to_string(DepositInfoS.amount_by_the_end)));
}

void s21_FinanceWindow::on_Clear_2_clicked() {
  ui->DepositAmount_2->setText("");
  ui->Term_2->setText("");
  ui->InterestRate_2->setText("");
  ui->TaxRate->setText("");

  ui->AccuredInterest->setText("");
  ui->TaxAmount->setText("");
  ui->AmountByTheEnd->setText("");
}

void s21_FinanceWindow::on_YesCap_clicked() { ui->NoCap->setChecked(false); }

void s21_FinanceWindow::on_NoCap_clicked() { ui->YesCap->setChecked(false); }
