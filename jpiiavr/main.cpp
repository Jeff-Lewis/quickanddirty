/*******************************************************************************
  Application name: jpiiAVR
  Filename: main.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/

#include <QtGui/QApplication>
#include <QCoreApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Juhapekka Piiroinen");
    QCoreApplication::setOrganizationDomain("http://code.google.com/p/quickanddirty");
    QCoreApplication::setApplicationName("jpiiAVR");

    MainWindow w;
    w.show();
    return a.exec();
}
