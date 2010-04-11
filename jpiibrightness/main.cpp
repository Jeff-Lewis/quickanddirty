/*!
  The purpose of this application is to enable brightness changing without terminal application

  \file main.cpp
  \author Juhapekka Piiroinen
  \date 11.4.2010
  GNU/GPLv3
  http://code.google.com/p/quickanddirty
*/
#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
