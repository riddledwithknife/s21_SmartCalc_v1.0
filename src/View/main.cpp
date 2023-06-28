#include <QApplication>

#include "s21_mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21_MainWindow w;

  w.setWindowTitle("SmartCalc");
  w.show();

  return a.exec();
}
