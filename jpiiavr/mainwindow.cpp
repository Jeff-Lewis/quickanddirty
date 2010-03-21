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
    DIN
        ui->setupUi(this);
        this->avrDude = new QProcess(parent);
        this->licenseDialog = new LicenseDialog(this);
        this->codeEditor = new CodeEditor(this);
        if (!ui->scrollAreaCodeEditor->layout()) {
            ui->scrollAreaCodeEditor->setLayout(new QVBoxLayout());
            ui->scrollAreaCodeEditor->layout()->setMargin(0);
        }
        ui->scrollAreaCodeEditor->layout()->addWidget(this->codeEditor);
        ui->widgetDatasheetActions->setVisible(false);
        ui->pushButtonSaveChanges->setEnabled(false);
        connectComponents();
        fillComboboxes();
        restoreSettings();
        loadHelp();
    DOUT
}

void MainWindow::handleScaleFactorChanged(double value)
{
    Q_UNUSED(value);
    DIN
        this->handleDatasheetGotoPage(ui->spinBoxCurrentPage->value());
    DOUT
}

void MainWindow::handleSourceCodeEdited()
{
    DIN
        ui->pushButtonSaveChanges->setEnabled(true);
    DOUT
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    DIN
        QMainWindow::closeEvent(event);
        saveSettings();
    DOUT
}

void MainWindow::handleSourceCodeFilenameChanged()
{
    DIN
        QString filename = ui->lineEditSourceCodeFilename->text();
        if (QFile::exists(filename)) {
            QFile sourceFile(filename);
            if (sourceFile.open(QIODevice::ReadOnly)) {
                if (sourceFile.bytesAvailable()>0) {
                    this->codeEditor->setPlainText(QString(sourceFile.readAll()));
                }
                sourceFile.close();
            }
        }
    DOUT
}

void MainWindow::handleSaveSourceCode()
{
    DIN
        QString filename = ui->lineEditSourceCodeFilename->text();
        QFile fileSourceCode(filename);
        if (fileSourceCode.open(QIODevice::WriteOnly)) {
            fileSourceCode.write(this->codeEditor->toPlainText().toAscii());
            fileSourceCode.close();
        }
        ui->pushButtonSaveChanges->setEnabled(false);
    DOUT
}

void MainWindow::handleOpenSourceCode()
{
    DIN
        QString filename = QFileDialog::getOpenFileName(this,"Open Source Code","","*.c");
        if (filename.isNull()==false && QFile(filename).exists()) {
            ui->lineEditSourceCodeFilename->setText(filename);
            handleSourceCodeFilenameChanged();
        }
    DOUT
}

void MainWindow::handleDatasheetGotoPage(int page)
{
    DIN
        double scaleFactor = ui->doubleSpinBoxScaleFactor->value();
        if (page>doc->numPages()) {
            qWarning() << "too large page number";
            return;
        } else if (page<1) {
            qWarning() << "too small page number";
            return;
        }
        if (page==doc->numPages()) {
            ui->pushButtonNextPage->setEnabled(false);
        } else {
            ui->pushButtonNextPage->setEnabled(true);
        }
        if (page==1) {
            ui->pushButtonPreviousPage->setEnabled(false);
        } else {
            ui->pushButtonPreviousPage->setEnabled(true);
        }
        page -= 1;

        qDebug() << "rendering..";
        QImage image = doc->page(page)->renderToImage(scaleFactor * this->physicalDpiX(),scaleFactor * this->physicalDpiY());
        qDebug() << "rendering done!";
        if (ui->graphicsViewDatasheet->scene()) {
            ui->graphicsViewDatasheet->scene()->clear();
        } else {
            ui->graphicsViewDatasheet->setScene(new QGraphicsScene());
        }
        ui->graphicsViewDatasheet->scene()->addPixmap(QPixmap::fromImage(image));
        ui->graphicsViewDatasheet->resize(image.size());
        ui->widgetDatasheetActions->setVisible(true);
    DOUT
}

void MainWindow::handleDatasheetNextPage()
{
    DIN
        if (ui->spinBoxCurrentPage->value()<doc->numPages()) {
            ui->spinBoxCurrentPage->setValue(ui->spinBoxCurrentPage->value()+1);
        }
    DOUT
}

void MainWindow::handleDatasheetPreviousPage()
{
    DIN
        if (ui->spinBoxCurrentPage->value()>0) {
            ui->spinBoxCurrentPage->setValue(ui->spinBoxCurrentPage->value()-1);
        }
    DOUT
}

void MainWindow::handleShowLicense()
{
    DIN
            this->licenseDialog->exec();
    DOUT
}

void MainWindow::handleOpenDatasheet()
{
    DIN
        this->doc = Poppler::Document::load(ui->comboBoxDatasheets->itemData(ui->comboBoxDatasheets->currentIndex()).toString());
        ui->spinBoxCurrentPage->setMaximum(this->doc->numPages());
        ui->labelMaxPages->setText(QString("/%0").arg(this->doc->numPages()));
        handleDatasheetGotoPage(1);
    DOUT
}

void MainWindow::loadHelp()
{
    DIN
        ui->textEditHelp->setHtml("<img src=\":/avrtargetboards_1.jpg\" /><br /><img src=\":/avrtargetboards_2.jpg\" /><br />More @ <a href=\"http://www.evilmadscientist.com/article.php/avrtargetboards/\">http://www.evilmadscientist.com/article.php/avrtargetboards/</a>.");
    DOUT
}

/********************************************************************************
  restore settings, slot for restore settings button as well
********************************************************************************/
void MainWindow::restoreSettings()
{
    DIN
        ui->lineEditAVRDude->setText(this->settings.value(ui->lineEditAVRDude->objectName(),QString(AVRDUDE)).toString());
        ui->comboBoxProgrammer->setCurrentIndex(this->settings.value(ui->comboBoxProgrammer->objectName(),0).toInt());
        ui->lineEditPort->setText(this->settings.value(ui->lineEditPort->objectName(),"usb").toString());
        ui->comboBoxAVR->setCurrentIndex(this->settings.value(ui->comboBoxAVR->objectName(),0).toInt());
        ui->lineEditFlash->setText(this->settings.value(ui->lineEditFlash->objectName()).toString());
        // this->codeEditor->setPlainText(this->settings.value(this->codeEditor->objectName()).toString());
        ui->lineEditSourceCodeFilename->setText(this->settings.value(ui->lineEditSourceCodeFilename->objectName()).toString());
        handleSourceCodeFilenameChanged();
    DOUT
}


/********************************************************************************
  save settings, slot for save settings button as well
********************************************************************************/
void MainWindow::saveSettings()
{
    DIN
        this->settings.setValue(ui->lineEditAVRDude->objectName(),ui->lineEditAVRDude->text());
        this->settings.setValue(ui->comboBoxProgrammer->objectName(),ui->comboBoxProgrammer->currentIndex());
        this->settings.setValue(ui->lineEditPort->objectName(),ui->lineEditPort->text());
        this->settings.setValue(ui->comboBoxAVR->objectName(),ui->comboBoxAVR->currentIndex());
        this->settings.setValue(ui->lineEditFlash->objectName(),ui->lineEditFlash->text());
        this->settings.setValue(ui->lineEditSourceCodeFilename->objectName(),ui->lineEditSourceCodeFilename->text());
        //this->settings.setValue(this->codeEditor->objectName(),this->codeEditor->toPlainText());
    DOUT
}

/********************************************************************************
  connect signals and slots
********************************************************************************/
void MainWindow::connectComponents()
{
    DIN
        connect(ui->pushButtonBrowse,SIGNAL(clicked()),this,SLOT(handleBrowseFlash()));
        connect(ui->pushButtonWrite,SIGNAL(clicked()),this,SLOT(handleWriteFlash()));
        connect(ui->pushButtonRead,SIGNAL(clicked()),this,SLOT(handleReadFlash()));
        connect(ui->pushButtonTest,SIGNAL(clicked()),this,SLOT(handleTestConnection()));
        connect(ui->pushButtonSaveSettings,SIGNAL(clicked()),this,SLOT(saveSettings()));
        connect(ui->pushButtonRestoreSettings,SIGNAL(clicked()),this,SLOT(restoreSettings()));
        connect(ui->pushButtonOpenDatasheet,SIGNAL(clicked()),this,SLOT(handleOpenDatasheet()));
        connect(ui->pushButtonLicense,SIGNAL(clicked()),this,SLOT(handleShowLicense()));
        connect(ui->pushButtonNextPage,SIGNAL(clicked()),this,SLOT(handleDatasheetNextPage()));
        connect(ui->pushButtonPreviousPage,SIGNAL(clicked()),this,SLOT(handleDatasheetPreviousPage()));
        connect(ui->spinBoxCurrentPage,SIGNAL(valueChanged(int)),this,SLOT(handleDatasheetGotoPage(int)));
        connect(ui->pushButtonOpenSource,SIGNAL(clicked()),this,SLOT(handleOpenSourceCode()));
        connect(ui->lineEditSourceCodeFilename,SIGNAL(returnPressed()),this,SLOT(handleSourceCodeFilenameChanged()));
        connect(ui->pushButtonSaveChanges,SIGNAL(clicked()),this,SLOT(handleSaveSourceCode()));

        connect(this->codeEditor,SIGNAL(textChanged()),this,SLOT(handleSourceCodeEdited()));
        connect(ui->doubleSpinBoxScaleFactor,SIGNAL(valueChanged(double)),this,SLOT(handleScaleFactorChanged(double)));

        connect(this->avrDude,SIGNAL(readyReadStandardOutput()),this,SLOT(handleAvrDudeStdout()));
        connect(this->avrDude,SIGNAL(readyRead()),this,SLOT(handleAvrDudeStdout()));
        connect(this->avrDude,SIGNAL(readyReadStandardError()),this,SLOT(handleAvrDudeStdout()));
        connect(this->avrDude,SIGNAL(started()),this,SLOT(handleAvrDudeStarted()));
        connect(this->avrDude,SIGNAL(finished(int)),this,SLOT(handleAvrDudeFinished(int)));
    DOUT
}

/********************************************************************************
  handle qprocess signal started(), disable other possible actions
********************************************************************************/
void MainWindow::handleAvrDudeStarted()
{
    DIN
        ui->widgetActions->setEnabled(false);
    DOUT
}

/********************************************************************************
  handle qprocess signal finished(int), enable other possible actions
********************************************************************************/
void MainWindow::handleAvrDudeFinished(int val)
{
    DIN
        Q_UNUSED(val);
        ui->widgetActions->setEnabled(true);
    DOUT
}

/********************************************************************************
  handle stdout/stderr from qprocess
********************************************************************************/
void MainWindow::handleAvrDudeStdout()
{
    DIN
            QString stdout(this->avrDude->readAllStandardOutput());
        QString stderr(this->avrDude->readAllStandardError());
        QString out(this->avrDude->readAll());
        ui->textEditTerminal->append(stdout);
        ui->textEditTerminal->append(stderr);
        ui->textEditTerminal->append(out);
    DOUT
}

/********************************************************************************
  fill avr device list and programmer list from txt -files
********************************************************************************/
void MainWindow::fillComboboxes()
{
    DIN
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

        QDir dir;
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        dir.setPath(QString("%0/datasheets").arg(QCoreApplication::applicationDirPath()));
        QStringList filterNames;
        filterNames << "*.pdf";
        dir.setNameFilters(filterNames);
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            ui->comboBoxDatasheets->addItem(fileInfo.fileName(),fileInfo.absoluteFilePath());
        }
    DOUT
}

/********************************************************************************
  show open file dialog
********************************************************************************/
void MainWindow::handleBrowseFlash()
{
    DIN
        QString filename = QFileDialog::getOpenFileName(this,"Locate Flash file for uploading to AVR","","*.hex");
        if (filename.isNull()==false && QFile(filename).exists()) {
            ui->lineEditFlash->setText(filename);
        }
    DOUT
}

/********************************************************************************
  show save file dialog
********************************************************************************/
void MainWindow::handleBrowseFlashRead()
{
    DIN
        QString filename = QFileDialog::getSaveFileName(this,"Select Flash file for downloading from AVR","flash.hex","*.hex");
        if (filename.isNull()==false) {
            ui->lineEditFlash->setText(filename);
        }
    DOUT
}

/********************************************************************************
  start qprocess for reading flash from avr to file
********************************************************************************/
void MainWindow::handleReadFlash()
{
    DIN
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
    DOUT
}


/********************************************************************************
  start qprocess for writing flash to avr from file
********************************************************************************/
void MainWindow::handleWriteFlash()
{
    DIN
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
    DOUT
}

/********************************************************************************
  start qprocess for testing current settings without read or write flash
********************************************************************************/
void MainWindow::handleTestConnection()
{
    DIN
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
    DOUT
}


/********************************************************************************
  deconstructor, check that qprocess is not running and free pointers
********************************************************************************/
MainWindow::~MainWindow()
{
    DIN
        delete ui;
        if (avrDude->isOpen()) {
            avrDude->close();
        }
        delete avrDude;
    DOUT
}
