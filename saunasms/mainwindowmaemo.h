#ifndef MAINWINDOWMAEMO_H
#define MAINWINDOWMAEMO_H

#include <QMainWindow>

namespace Ui {
    class MainWindowMaemo;
}

class MainWindowMaemo : public QMainWindow {
    Q_OBJECT
public:
    MainWindowMaemo(QWidget *parent = 0);
    ~MainWindowMaemo();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindowMaemo *ui;
};

#endif // MAINWINDOWMAEMO_H
