#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QDateTime>
#include <QDesktopServices>

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
    void on_pushButtonScan_clicked();
    void on_pushButtonStopScanning_clicked();
    void scanner_finished(int);
    void scanner_started();

private:
    void enableScanUi();
    void disableScanUi();
    Ui::MainWindow *ui;
    QString scanApp;
    QProcess *processScan;
};

#endif // MAINWINDOW_H
