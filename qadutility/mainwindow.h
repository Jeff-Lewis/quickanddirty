#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QCryptographicHash>
#include <QtScript>

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
    void HandleTextChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
