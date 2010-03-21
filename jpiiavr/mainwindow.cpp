/*******************************************************************************
  Application name: jpiiAVR
  Filename: mainwindow.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/********************************************************************************
  main constructor
********************************************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->avrDude = new QProcess(parent);
    connectComponents();
    fillComboboxes();
    loadLicense();
    restoreSettings();
    loadHelp();
}

void MainWindow::handleOpenDatasheet() {
    this->doc = Poppler::Document::load(ui->comboBoxDatasheets->currentText());
    int scaleFactor = 1;
    QImage image = doc->page(0)->renderToImage(scaleFactor * physicalDpiX(),scaleFactor * physicalDpiY());
    if (!ui->graphicsViewDatasheet->scene()) {
        ui->graphicsViewDatasheet->setScene(new QGraphicsScene());
    }
    ui->graphicsViewDatasheet->scene()->addPixmap(QPixmap::fromImage(image));
}

void MainWindow::loadHelp() {
    ui->textEditHelp->setHtml("<img src=\":/avrtargetboards_1.jpg\" /><br /><img src=\":/avrtargetboards_2.jpg\" /><br />More @ <a href=\"http://www.evilmadscientist.com/article.php/avrtargetboards/\">http://www.evilmadscientist.com/article.php/avrtargetboards/</a>.");
}

/********************************************************************************
  load application license
********************************************************************************/
void MainWindow::loadLicense() {
    QFile fileLicense(":/gpl-3.0.txt");
    QString license = "http://gplv3.fsf.org/";
    if (fileLicense.open(QIODevice::ReadOnly)) {
        license = QString(fileLicense.readAll());
    }
    ui->plainTextEditLicense->setPlainText(license);
}

/********************************************************************************
  restore settings, slot for restore settings button as well
********************************************************************************/
void MainWindow::restoreSettings() {
    ui->lineEditAVRDude->setText(this->settings.value(ui->lineEditAVRDude->objectName(),QString(AVRDUDE)).toString());
    ui->comboBoxProgrammer->setCurrentIndex(this->settings.value(ui->comboBoxProgrammer->objectName(),0).toInt());
    ui->lineEditPort->setText(this->settings.value(ui->lineEditPort->objectName(),"usb").toString());
    ui->comboBoxAVR->setCurrentIndex(this->settings.value(ui->comboBoxAVR->objectName(),0).toInt());
    ui->lineEditFlash->setText(this->settings.value(ui->lineEditFlash->objectName()).toString());
}


/********************************************************************************
  save settings, slot for save settings button as well
********************************************************************************/
void MainWindow::saveSettings() {
    this->settings.setValue(ui->lineEditAVRDude->objectName(),ui->lineEditAVRDude->text());
    this->settings.setValue(ui->comboBoxProgrammer->objectName(),ui->comboBoxProgrammer->currentIndex());
    this->settings.setValue(ui->lineEditPort->objectName(),ui->lineEditPort->text());
    this->settings.setValue(ui->comboBoxAVR->objectName(),ui->comboBoxAVR->currentIndex());
    this->settings.setValue(ui->lineEditFlash->objectName(),ui->lineEditFlash->text());
}

/********************************************************************************
  connect signals and slots
********************************************************************************/
void MainWindow::connectComponents() {
    connect(ui->pushButtonBrowse,SIGNAL(clicked()),this,SLOT(handleBrowseFlash()));
    connect(ui->pushButtonWrite,SIGNAL(clicked()),this,SLOT(handleWriteFlash()));
    connect(ui->pushButtonRead,SIGNAL(clicked()),this,SLOT(handleReadFlash()));
    connect(ui->pushButtonTest,SIGNAL(clicked()),this,SLOT(handleTestConnection()));
    connect(ui->pushButtonSaveSettings,SIGNAL(clicked()),this,SLOT(saveSettings()));
    connect(ui->pushButtonRestoreSettings,SIGNAL(clicked()),this,SLOT(restoreSettings()));
    connect(ui->pushButtonOpenDatasheet,SIGNAL(clicked()),this,SLOT(handleOpenDatasheet()));
    connect(this->avrDude,SIGNAL(readyReadStandardOutput()),this,SLOT(handleAvrDudeStdout()));
    connect(this->avrDude,SIGNAL(readyRead()),this,SLOT(handleAvrDudeStdout()));
    connect(this->avrDude,SIGNAL(readyReadStandardError()),this,SLOT(handleAvrDudeStdout()));
    connect(this->avrDude,SIGNAL(started()),this,SLOT(handleAvrDudeStarted()));
    connect(this->avrDude,SIGNAL(finished(int)),this,SLOT(handleAvrDudeFinished(int)));
}

/********************************************************************************
  handle qprocess signal started(), disable other possible actions
********************************************************************************/
void MainWindow::handleAvrDudeStarted() {
    ui->widgetActions->setEnabled(false);
}

/********************************************************************************
  handle qprocess signal finished(int), enable other possible actions
********************************************************************************/
void MainWindow::handleAvrDudeFinished(int val) {
    Q_UNUSED(val);
    ui->widgetActions->setEnabled(true);
}

/********************************************************************************
  handle stdout/stderr from qprocess
********************************************************************************/
void MainWindow::handleAvrDudeStdout() {
    QString stdout(this->avrDude->readAllStandardOutput());
    QString stderr(this->avrDude->readAllStandardError());
    QString out(this->avrDude->readAll());
    ui->textEditTerminal->append(stdout);
    ui->textEditTerminal->append(stderr);
    ui->textEditTerminal->append(out);
}

/********************************************************************************
  fill avr device list and programmer list from txt -files
********************************************************************************/
void MainWindow::fillComboboxes() {
    QFile fileAvrDevices(QString("%0/avrdevices.txt").arg(QApplication::applicationDirPath()));
    if (fileAvrDevices.exists() && fileAvrDevices.open(QIODevice::ReadOnly)) {
        QStringList lines = QString(fileAvrDevices.readAll()).split("\n");
        fileAvrDevices.close();

        while (lines.empty()==false) {
            QStringList lineData = QString(lines.takeFirst()).split(";");
            if (lineData.count()==2) {
                QString desc = lineData.takeLast().trimmed();
                QString id = lineData.takeFirst().trimmed();
                ui->comboBoxAVR->addItem(QString("%0 (%1)").arg(desc).arg(id),id);
            }
        }
    } else {
        ui->comboBoxAVR->addItem("avrdevices.txt not found");
    }

    QFile fileProgrammer(QString("%0/programmer.txt").arg(QApplication::applicationDirPath()));
    if (fileProgrammer.exists() && fileProgrammer.open(QIODevice::ReadOnly)) {
        QStringList lines = QString(fileProgrammer.readAll()).split("\n");
        fileProgrammer.close();

        while (lines.empty()==false) {
            QStringList lineData = QString(lines.takeFirst()).split(";");
            if (lineData.count()==2) {
                QString desc = lineData.takeLast().trimmed();
                QString id = lineData.takeFirst().trimmed();
                ui->comboBoxProgrammer->addItem(QString("%0 (%1)").arg(desc).arg(id),id);
            }
        }
    } else {
        ui->comboBoxAVR->addItem("programmer.txt not found");
    }

}

/********************************************************************************
  show open file dialog
********************************************************************************/
void MainWindow::handleBrowseFlash() {
    QString filename = QFileDialog::getOpenFileName(this,"Locate Flash file for uploading to AVR","","*.hex");
    if (filename.isNull()==false && QFile(filename).exists()) {
        ui->lineEditFlash->setText(filename);
    }
}

/********************************************************************************
  show save file dialog
********************************************************************************/
void MainWindow::handleBrowseFlashRead() {
    QString filename = QFileDialog::getSaveFileName(this,"Select Flash file for downloading from AVR","flash.hex","*.hex");
    if (filename.isNull()==false) {
        ui->lineEditFlash->setText(filename);
    }
}

/********************************************************************************
  start qprocess for reading flash from avr to file
********************************************************************************/
void MainWindow::handleReadFlash() {
    QString programmerId = ui->comboBoxProgrammer->itemData(ui->comboBoxProgrammer->currentIndex()).toString();
    QString avrId = ui->comboBoxAVR->itemData(ui->comboBoxAVR->currentIndex()).toString();
    QString portName = ui->lineEditAVRDude->text();
    if (ui->lineEditFlash->text().isEmpty()) {
        handleBrowseFlashRead();
        if (ui->lineEditFlash->text().isEmpty()) {
            return;
        }
    }
    QString flashName = ui->lineEditFlash->text();
    QStringList arguments;
    arguments << "-v";
    arguments << "-c" << programmerId;
    arguments << "-p" << avrId;
    arguments << "-P" << portName;
    arguments << "-U" << QString("flash:r:%0").arg(flashName);
    QString command(AVRDUDE);
    ui->textEditTerminal->clear();
    ui->textEditTerminal->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
    this->avrDude->start(command,arguments);
}


/********************************************************************************
  start qprocess for writing flash to avr from file
********************************************************************************/
void MainWindow::handleWriteFlash() {
    QString programmerId = ui->comboBoxProgrammer->itemData(ui->comboBoxProgrammer->currentIndex()).toString();
    QString avrId = ui->comboBoxAVR->itemData(ui->comboBoxAVR->currentIndex()).toString();
    QString portName = ui->lineEditPort->text();
    if (ui->lineEditFlash->text().isEmpty()) {
        handleBrowseFlash();
        if (ui->lineEditFlash->text().isEmpty()) {
            return;
        }
    }
    QString flashName = ui->lineEditFlash->text();
    QStringList arguments;
    arguments << "-v";
    arguments << "-c" << programmerId;
    arguments << "-p" << avrId;
    arguments << "-P" << portName;
    arguments << "-U" << QString("flash:w:%0").arg(flashName);
    QString command(ui->lineEditAVRDude->text());
    ui->textEditTerminal->clear();
    ui->textEditTerminal->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
    this->avrDude->start(command,arguments);
}

/********************************************************************************
  start qprocess for testing current settings without read or write flash
********************************************************************************/
void MainWindow::handleTestConnection() {
    QString programmerId = ui->comboBoxProgrammer->itemData(ui->comboBoxProgrammer->currentIndex()).toString();
    QString avrId = ui->comboBoxAVR->itemData(ui->comboBoxAVR->currentIndex()).toString();
    QString portName = ui->lineEditPort->text();
    QString flashName = ui->lineEditFlash->text();
    QStringList arguments;
    arguments << "-v";
    arguments << "-c" << programmerId;
    arguments << "-p" << avrId;
    arguments << "-P" << portName;
    QString command(ui->lineEditAVRDude->text());
    ui->textEditTerminal->clear();
    ui->textEditTerminal->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
    this->avrDude->start(command,arguments);
}


/********************************************************************************
  deconstructor, check that qprocess is not running and free pointers
********************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
    if (avrDude->isOpen()) {
        avrDude->close();
    }
    delete avrDude;
}
