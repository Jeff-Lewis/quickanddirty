/*!
  The purpose of this application is to enable brightness changing without terminal application

  \file mainwindow.cpp
  \author Juhapekka Piiroinen
  \date 11.4.2010
  GNU/GPLv3
  http://code.google.com/p/quickanddirty
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_lineEditDevice_editingFinished();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditDevice_editingFinished()
{
    if (deviceName.isOpen()) {
        deviceName.close();
    }
    deviceName.setFileName(ui->lineEditDevice->text());

    bool ok = deviceName.exists() && deviceName.open(QIODevice::ReadWrite);
    ui->plainTextEditStdErr->appendPlainText(QString("Device exists: %0").arg(deviceName.exists()?"true":"false"));
    ui->plainTextEditStdErr->appendPlainText(QString("Device opened for read/write: %0").arg(ok?"true":"false"));
    ui->pushButtonSetValue->setEnabled(ok);
    if (ok==false && deviceName.exists()) {
        deviceName.open(QIODevice::ReadOnly);
        ui->plainTextEditStdErr->appendPlainText("Device is read-only for this user!");
    }
    if (deviceName.exists() && deviceName.isReadable()) {
        ui->plainTextEditStdout->setPlainText(deviceName.readAll());
        QStringList lines = ui->plainTextEditStdout->toPlainText().split("\n");
        QStringList options = lines.takeFirst().split(":").takeLast().trimmed().split(" ");
        ui->comboBoxValue->clear();
        ui->comboBoxValue->addItems(options);
        QString curValue = lines.takeFirst().split(":").takeLast().trimmed();
        ui->comboBoxValue->setCurrentIndex(ui->comboBoxValue->findText(curValue));
    }
}

void MainWindow::on_pushButtonSetValue_clicked()
{
    if (deviceName.isOpen()==false || deviceName.isReadable()==false || deviceName.isWritable()==false)
    {
        ui->plainTextEditStdErr->appendPlainText("Device is not open");
        on_lineEditDevice_editingFinished();
        return;
    }

    deviceName.write(ui->comboBoxValue->currentText().toAscii());
}

