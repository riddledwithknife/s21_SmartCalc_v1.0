#ifndef S21_FINANCEWINDOW_H
#define S21_FINANCEWINDOW_H

#include <QWidget>

#include "ui_s21_financewindow.h"

extern "C" {
#include "../Model/finance_calc.h"
};

namespace Ui {
class s21_FinanceWindow;
}

class s21_FinanceWindow : public QWidget {
  Q_OBJECT

 public:
  explicit s21_FinanceWindow(QWidget *parent = nullptr);
  ~s21_FinanceWindow();

 private slots:
  void on_CREDITCALCMENU_clicked();

  void on_DEPOSITCALCMENU_clicked();

  void on_Calculate_clicked();

  void on_Clear_clicked();

  void on_Annuity_clicked();

  void on_Differentiated_clicked();

  void on_Calculate_2_clicked();

  void on_Clear_2_clicked();

  void on_YesCap_clicked();

  void on_NoCap_clicked();

 private:
  Ui::s21_FinanceWindow *ui;
};

#endif  // S21_FINANCEWINDOW_H
