#include "mainwindowmaemo.h"
#include "ui_mainwindowmaemo.h"

MainWindowMaemo::MainWindowMaemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowMaemo)
{
    ui->setupUi(this);
}

MainWindowMaemo::~MainWindowMaemo()
{
    delete ui;
}

void MainWindowMaemo::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
