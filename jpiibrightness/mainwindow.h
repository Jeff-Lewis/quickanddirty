/*!
  The purpose of this application is to enable brightness changing without terminal application

  \file mainwindow.h
  \author Juhapekka Piiroinen
  \date 11.4.2010
  GNU/GPLv3
  http://code.google.com/p/quickanddirty
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QFile>

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

protected slots:
    void on_lineEditDevice_editingFinished();
    void on_pushButtonSetValue_clicked();

private:
    Ui::MainWindow *ui;
    QFile deviceName;
};

#endif // MAINWINDOW_H
