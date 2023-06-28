#ifndef S21_MAINWINDOW_H
#define S21_MAINWINDOW_H

#include <QMainWindow>

#include "s21_financewindow.h"
#include "ui_s21_mainwindow.h"

extern "C" {
#include "../Model/polish.h"
};

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_MainWindow;
}
QT_END_NAMESPACE

class s21_MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  s21_MainWindow(QWidget *parent = nullptr);
  ~s21_MainWindow();

 private slots:

  void on_Zero_clicked();

  void on_One_clicked();

  void on_Two_clicked();

  void on_Three_clicked();

  void on_Four_clicked();

  void on_Five_clicked();

  void on_Six_clicked();

  void on_Seven_clicked();

  void on_Eight_clicked();

  void on_Nine_clicked();

  void on_Add_clicked();

  void on_Minus_clicked();

  void on_Mul_clicked();

  void on_Div_clicked();

  void on_Comma_clicked();

  void on_Mod_clicked();

  void on_X_clicked();

  void on_NegVar_clicked();

  void on_PlusVar_clicked();

  void on_Pow_clicked();

  void on_Sqrt_clicked();

  void on_StaplesClose_clicked();

  void on_StaplesOpen_clicked();

  void on_Equal_clicked();

  void on_Del_clicked();

  void on_Clear_clicked();

  void on_SINCOSMENU_clicked();

  void on_MAINMENU_clicked();

  void on_Sin_clicked();

  void on_Cos_clicked();

  void on_Tan_clicked();

  void on_Asin_clicked();

  void on_Acos_clicked();

  void on_Atan_clicked();

  void on_Log_clicked();

  void on_Ln_clicked();

  void on_actionFinancial_Mode_triggered();

  void on_actionMain_Mode_triggered();

 private:
  Ui::s21_MainWindow *ui;
  s21_FinanceWindow *FWindow = new s21_FinanceWindow();
};

#endif  // S21_MAINWINDOW_H
