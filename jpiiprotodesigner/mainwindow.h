/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: mainwindow.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include "protopieceitem.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QFile>
#include <QStringList>
#include "pdip.h"
#include "resistor.h"
#include "to92.h"
#include "to220.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleSaveAsPng();
    void handlePrint();
    void handleSaveToFile();
    void handleLoadFromFile();
    void HandleAddPDIP();
    void HandleAddResistor();
    void HandleAddTo92();
    void HandleAddTo220();

private:
    Ui::MainWindow *ui;
    QList<ProtoPieceItem*> ruudut;

};

#endif // MAINWINDOW_H
