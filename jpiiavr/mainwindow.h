/*******************************************************************************
  Application name: jpiiAVR
  Filename: mainwindow.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/

/////////////////////////////////////////////////////////////////////////////////
//avr-gcc -mmcu=atmega8 -o interrupts.elf interrupts.c
//avr-objcopy -R .eeprom -O ihex interrupts.elf interrupts.hex
//avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex interrupts.elf interrupts.eep
//avr-objdump -S interrupts.elf > interrupts.lss
/////////////////////////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QSettings>

#include <poppler-qt4.h>

#include "codeeditor.h"
#include "licensedialog.h"
#include "common.h"

#define AVRDUDE "/usr/bin/avrdude"
#define AVRGCC "/usr/bin/avr-gcc"
#define AVROBJCOPY "/usr/bin/avr-objcopy"
#define AVREEPROM "avreeprom"

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
    virtual void closeEvent(QCloseEvent *event);
    void handleBrowseFlash();
    void handleWriteFlash();
    void handleTestConnection();
    void handleAvrDudeStdout();
    void handleAvrDudeFinished(int);
    void handleAvrDudeStarted();
    void handleBrowseFlashRead();
    void handleReadFlash();
    void restoreSettings();
    void saveSettings();
    void handleOpenDatasheet();
    void handleShowLicense();
    void handleDatasheetGotoPage(int);
    void handleDatasheetNextPage();
    void handleDatasheetPreviousPage();
    void handleOpenSourceCode();
    void handleSaveSourceCode();
    void handleSourceCodeFilenameChanged();
    void handleSourceCodeEdited();
    void handleScaleFactorChanged(double);
    void handleCompile();
    void handleCompilerStdout();
    void handleCompilerFinished(int);
    void handleCompilerStarted();
    void handleCompileFlash();
    void handleCompileEeprom();
    void handleCreateNew();
    void handleEditCode();

protected:
    void connectComponents();
    void fillComboboxes();
    void loadHelp();

private:
    Ui::MainWindow *ui;
    QProcess* avrDude;
    QProcess* compiler;
    QSettings settings;
    Poppler::Document *doc;
    LicenseDialog* licenseDialog;
    CodeEditor* codeEditor;
    QString compilerMode;
};

#endif // MAINWINDOW_H
