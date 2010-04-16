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
        this->compiler = new QProcess(parent);
        this->licenseDialog = new LicenseDialog(this);
        this->codeEditor = new CodeEditor(this);
        this->compileErrorMsgs = new QStringListModel();
        this->otherErrorMsgs = new QStringListModel();
        if (!ui->scrollAreaCodeEditor->layout()) {
            ui->scrollAreaCodeEditor->setLayout(new QVBoxLayout());
            ui->scrollAreaCodeEditor->layout()->setMargin(0);
        }
        ui->scrollAreaCodeEditor->layout()->addWidget(this->codeEditor);
        ui->widgetDatasheetActions->setVisible(false);
        ui->actionSave_Changes->setEnabled(false);
        connectComponents();
        fillComboboxes();
        restoreSettings();
        loadHelp();
        ui->statusBar->addPermanentWidget(new QLabel("Author: Juhapekka Piiroinen"));
        ui->statusBar->addPermanentWidget(new QLabel("License: GNU/GPLv3"));
        ui->listViewCompileErrors->setModel(this->compileErrorMsgs);
        ui->listViewOtherErrors->setModel(this->otherErrorMsgs);
    DOUT
}

void MainWindow::handleAutomaticCompile() {
    DIN;
        if (ui->checkBoxAutomaticCompile->checkState()==Qt::Checked) {
            this->handleCompile();
        }
    DOUT;
}

void MainWindow::handleEditCode() {
    DIN;
        //ui->tabWidgetCoding->setCurrentIndex(0);
    DOUT;
}

void MainWindow::handleCreateNew()
{
    DIN
        ui->lineEditSourceCodeFilename->setText("");
        ui->lineEditFlash->setText("");
        QFile fileTemplate(QString("%0/template.txt").arg(QCoreApplication::applicationDirPath()));
        if (fileTemplate.open(QIODevice::ReadOnly)) {
            QString templateData = QString(fileTemplate.readAll());
            this->codeEditor->setPlainText(templateData);
        } else {
            this->codeEditor->setPlainText("");
        }
        ui->textEditTerminalCompiler->clear();
        ui->actionSave_Changes->setEnabled(true);
    DOUT
}

void MainWindow::handleCompileEeprom()
{
    DIN
        //avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex interrupts.elf interrupts.eep
        QString fileName = ui->lineEditSourceCodeFilename->text();
        QStringList arguments;
        arguments << "-j" << ".eeprom";
        arguments << "--change-section-lma" << ".eeprom=0";
        arguments << "-O" << "ihex";
        arguments << QString("%0.elf").arg(fileName);
        arguments << QString("%0.eep").arg(fileName);
        QString command(ui->lineEditAvrObjCopy->text());
        ui->textEditTerminalCompiler->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
        this->compilerMode = AVREEPROM;
        this->compiler->start(command,arguments);
    DOUT
}

void MainWindow::handleCompileFlash()
{
    DIN
        //avr-objcopy -R .eeprom -O ihex interrupts.elf interrupts.hex
        QString fileName = ui->lineEditSourceCodeFilename->text();
        QStringList arguments;
        arguments << "-R" << ".eeprom";
        arguments << "-O" << "ihex";
        arguments << QString("%0.elf").arg(fileName);
        arguments << QString("%0.hex").arg(fileName);
        QString command(ui->lineEditAvrObjCopy->text());
        ui->textEditTerminalCompiler->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
        this->compilerMode = AVROBJCOPY;
        this->compiler->start(command,arguments);
    DOUT
}

void MainWindow::handleCompile()
{
    DIN
        //ui->tabWidgetCoding->setCurrentIndex(1);
        if (ui->actionSave_Changes->isEnabled()) {
            this->handleSaveSourceCode();
        }
        //avr-gcc -mmcu=atmega8 -o interrupts.elf interrupts.c
        /*QFile fileCompiler("jpiiavr.c");
        if (fileCompiler.open(QIODevice::WriteOnly)==false) {
            ui->textEditTerminalCompiler->append("Failed to open temporary file for compiler!");
            return;
        }
        fileCompiler.write(this->codeEditor->toPlainText().toAscii());
        fileCompiler.close();*/
        QString fileName = ui->lineEditSourceCodeFilename->text();
        QStringList arguments;
        arguments << QString("-mmcu=%0").arg(ui->comboBoxAVR->itemText(ui->comboBoxAVR->currentIndex()).toLower());
        arguments << "-o" << QString("%0.elf").arg(fileName);
        arguments << fileName;
        QString command(ui->lineEditAvrGcc->text());
        ui->textEditTerminalCompiler->clear();
        ui->textEditTerminalCompiler->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
        this->compilerMode = AVRGCC;
        this->compiler->start(command,arguments);
    DOUT
}

void MainWindow::handleCompilerStdout()
{
    DIN
        QString stdout(this->compiler->readAllStandardOutput());
        QString stderr(this->compiler->readAllStandardError());
        QString out(this->compiler->readAll());
        qDebug() << "stdout:" << stdout;
        qDebug() << "stderr:" << stderr;
        qDebug() << "out:" << out;
        this->codeEditor->clearErrorLines();
        if (stderr.contains(":")) {
            QStringList lines = stderr.split("\n");
            if (this->compilerMode==AVRGCC) {
                QStringList curLines = this->compileErrorMsgs->stringList();
                curLines.append(lines);
                while (lines.empty()==false) {
                    QString lineData = lines.takeFirst();
                    QStringList lineDataItems = lineData.split(":");
                    if (lineDataItems.count()>4) {
                        if (lineDataItems.at(3).trimmed()=="warning") {
                            this->compileWarnings++;
                            this->codeEditor->addWarningLine(lineDataItems.at(1).trimmed().toInt());
                        } else if (lineDataItems.at(3).trimmed()=="error") {
                            this->compileErrors++;
                            this->codeEditor->addErrorLine(lineDataItems.at(1).trimmed().toInt());
                        }
                    } else if (lineDataItems.count()>2) {
                        if (lineDataItems.at(2).trimmed()=="warning") {
                            this->compileWarnings++;
                            this->codeEditor->addWarningLine(lineDataItems.at(1).trimmed().toInt());
                        } else if (lineDataItems.at(2).trimmed()=="error") {
                            this->compileErrors++;
                            this->codeEditor->addErrorLine(lineDataItems.at(1).trimmed().toInt());
                        }
                    }
                }
                this->compileErrorMsgs->setStringList(curLines);
            } else {
                QStringList curLines = this->otherErrorMsgs->stringList();
                curLines.append(lines);
                this->otherErrorMsgs->setStringList(curLines);
            }
        }
        this->codeEditor->repaint();
        ui->textEditTerminalCompiler->append(stdout);
        ui->textEditTerminalCompiler->append(stderr);
        ui->textEditTerminalCompiler->append(out);
    DOUT
}

void MainWindow::handleCompilerFinished(int value)
{
    DIN
        if (value==1) { //failed
            ui->textEditTerminalCompiler->append("==> Failed! :(");
            if (this->compilerMode==AVRGCC) {
                this->statusBar()->showMessage("Build failed! :(");
                ui->listViewCompileErrors->setStyleSheet("QListView::item { background-color:rgb(255,181,181) } QListView::item:selected { background-color:rgb(181,181,255) }");
                ui->tabWidgetMessages->setTabText(0,QString("avr-gcc (%0 warnings / %1 errors)").arg(this->compileWarnings).arg(this->compileErrors));
            } else if (this->compilerMode==AVROBJCOPY) {
                this->statusBar()->showMessage("Hex generation failed! :(");
                ui->listViewOtherErrors->setStyleSheet("QListView::item { background-color:rgb(255,181,181) } QListView::item:selected { background-color:rgb(181,181,255) }");
            } else {
                //TODO
            }
        } else {
            ui->textEditTerminalCompiler->append("==> Ok!");
            this->statusBar()->showMessage("Build OK!");
            if (this->compilerMode==AVRGCC) {
                this->handleCompileFlash();
                ui->listViewCompileErrors->setStyleSheet("QListView::item { background-color:rgb(181,255,181) } QListView::item:selected { background-color:rgb(181,181,255) }");
                ui->tabWidgetMessages->setTabText(0,QString("avr-gcc (%0 warnings / %1 errors)").arg(this->compileWarnings).arg(this->compileErrors));
            } else if (this->compilerMode==AVROBJCOPY) {
                ui->lineEditFlash->setText(QString("%0.hex").arg(ui->lineEditSourceCodeFilename->text()));
                this->handleCompileEeprom();
                ui->listViewOtherErrors->setStyleSheet("QListView::item { background-color:rgb(181,255,181) } QListView::item:selected { background-color:rgb(181,181,255) }");
            } else {
                //TODO
            }
        }
        ui->menuFlash->setEnabled(true);
        ui->menuBuild->setEnabled(true);
    DOUT
}

void MainWindow::handleCompilerStarted()
{
    DIN
        ui->menuFlash->setEnabled(false);
        ui->menuBuild->setEnabled(false);
        if (this->compilerMode==AVRGCC) {
            this->compileErrorMsgs->setStringList(QStringList());
            this->compileErrors = 0;
            this->compileWarnings = 0;
        } else {
            this->otherErrorMsgs->setStringList(QStringList());
        }
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
        ui->actionSave_Changes->setEnabled(true);
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
        if (filename.trimmed().length()==0) {
            filename = QFileDialog::getSaveFileName(this,"Save Source Code as..","","*.c");
            if (filename.length()==0) {
                return;
            }
            if (filename.endsWith(".c")==false) {
                filename.append(".c");
            }
            ui->lineEditSourceCodeFilename->setText(filename);
            fileSourceCode.setFileName(filename);
        }
        if (fileSourceCode.open(QIODevice::WriteOnly)) {
            fileSourceCode.write(this->codeEditor->toPlainText().toAscii());
            fileSourceCode.close();
        } else 
        ui->actionSave_Changes->setEnabled(false);
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
        ui->lineEditAvrGcc->setText(this->settings.value(ui->lineEditAvrGcc->objectName(),QString(AVRGCC)).toString());
        ui->comboBoxProgrammer->setCurrentIndex(this->settings.value(ui->comboBoxProgrammer->objectName(),0).toInt());
        ui->lineEditPort->setText(this->settings.value(ui->lineEditPort->objectName(),"usb").toString());
        ui->comboBoxAVR->setCurrentIndex(this->settings.value(ui->comboBoxAVR->objectName(),0).toInt());
        ui->lineEditFlash->setText(this->settings.value(ui->lineEditFlash->objectName()).toString());
        ui->lineEditAvrObjCopy->setText(this->settings.value(ui->lineEditAvrObjCopy->objectName(),QString(AVROBJCOPY)).toString());
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
        this->settings.setValue(ui->lineEditAvrGcc->objectName(),ui->lineEditAvrGcc->text());
        this->settings.setValue(ui->lineEditAvrObjCopy->objectName(),ui->lineEditAvrObjCopy->text());
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
        connect(ui->actionWrite_Flash,SIGNAL(triggered()),this,SLOT(handleWriteFlash()));
        connect(ui->actionRead_Flash,SIGNAL(triggered()),this,SLOT(handleReadFlash()));
        connect(ui->actionTest_Connection,SIGNAL(triggered()),this,SLOT(handleTestConnection()));
        connect(ui->pushButtonSaveSettings,SIGNAL(clicked()),this,SLOT(saveSettings()));
        connect(ui->pushButtonRestoreSettings,SIGNAL(clicked()),this,SLOT(restoreSettings()));
        connect(ui->pushButtonOpenDatasheet,SIGNAL(clicked()),this,SLOT(handleOpenDatasheet()));
        connect(ui->actionLicense,SIGNAL(triggered()),this,SLOT(handleShowLicense()));
        connect(ui->pushButtonNextPage,SIGNAL(clicked()),this,SLOT(handleDatasheetNextPage()));
        connect(ui->pushButtonPreviousPage,SIGNAL(clicked()),this,SLOT(handleDatasheetPreviousPage()));
        connect(ui->spinBoxCurrentPage,SIGNAL(valueChanged(int)),this,SLOT(handleDatasheetGotoPage(int)));
        connect(ui->pushButtonOpenSource,SIGNAL(clicked()),this,SLOT(handleOpenSourceCode()));
        connect(ui->lineEditSourceCodeFilename,SIGNAL(returnPressed()),this,SLOT(handleSourceCodeFilenameChanged()));
        connect(ui->actionSave_Changes,SIGNAL(triggered()),this,SLOT(handleSaveSourceCode()));
        connect(ui->actionCompile,SIGNAL(triggered()),this,SLOT(handleCompile()));
        connect(ui->actionGenerate_Flash,SIGNAL(triggered()),this,SLOT(handleCompileFlash()));
        connect(ui->actionGenerate_EEPROM,SIGNAL(triggered()),this,SLOT(handleCompileEeprom()));
        connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(handleCreateNew()));

        connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));

        connect(this->codeEditor,SIGNAL(textChanged()),this,SLOT(handleSourceCodeEdited()));
        connect(this->codeEditor,SIGNAL(textChanged()),this,SLOT(handleAutomaticCompile()));
        connect(ui->doubleSpinBoxScaleFactor,SIGNAL(valueChanged(double)),this,SLOT(handleScaleFactorChanged(double)));

        connect(this->avrDude,SIGNAL(readyReadStandardOutput()),this,SLOT(handleAvrDudeStdout()));
        connect(this->avrDude,SIGNAL(readyRead()),this,SLOT(handleAvrDudeStdout()));
        connect(this->avrDude,SIGNAL(readyReadStandardError()),this,SLOT(handleAvrDudeStdout()));
        connect(this->avrDude,SIGNAL(started()),this,SLOT(handleAvrDudeStarted()));
        connect(this->avrDude,SIGNAL(finished(int)),this,SLOT(handleAvrDudeFinished(int)));

        connect(this->compiler,SIGNAL(readyRead()),this,SLOT(handleCompilerStdout()));
        connect(this->compiler,SIGNAL(readyReadStandardError()),this,SLOT(handleCompilerStdout()));
        connect(this->compiler,SIGNAL(readyReadStandardOutput()),this,SLOT(handleCompilerStdout()));
        connect(this->compiler,SIGNAL(started()),this,SLOT(handleCompilerStarted()));
        connect(this->compiler,SIGNAL(finished(int)),this,SLOT(handleCompilerFinished(int)));
    DOUT
}

/********************************************************************************
  handle qprocess signal started(), disable other possible actions
********************************************************************************/
void MainWindow::handleAvrDudeStarted()
{
    DIN
        ui->menuFlash->setEnabled(false);
        ui->menuBuild->setEnabled(false);
    DOUT
}

/********************************************************************************
  handle qprocess signal finished(int), enable other possible actions
********************************************************************************/
void MainWindow::handleAvrDudeFinished(int val)
{
    DIN
        Q_UNUSED(val);
        ui->menuFlash->setEnabled(true);
        ui->menuBuild->setEnabled(true);
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
        ui->textEditTerminalCompiler->append(stdout);
        ui->textEditTerminalCompiler->append(stderr);
        ui->textEditTerminalCompiler->append(out);
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
                    ui->comboBoxAVR->addItem(QString("%0").arg(desc),id);
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
        ui->textEditTerminalCompiler->clear();
        ui->textEditTerminalCompiler->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
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
        ui->textEditTerminalCompiler->clear();
        ui->textEditTerminalCompiler->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
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
        ui->textEditTerminalCompiler->clear();
        ui->textEditTerminalCompiler->append(QString("%0 %1").arg(command).arg(arguments.join(" ")));
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
