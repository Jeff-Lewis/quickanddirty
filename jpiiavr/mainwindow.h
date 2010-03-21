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

#define AVRDUDE "/usr/bin/avrdude"

#define DIN qDebug() << ">>" << __FUNCTION__;
#define DOUT qDebug() << "<<" << __FUNCTION__;

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

protected:
    void connectComponents();
    void fillComboboxes();
    void loadHelp();

private:
    Ui::MainWindow *ui;
    QProcess* avrDude;
    QSettings settings;
    Poppler::Document *doc;
    LicenseDialog* licenseDialog;
    CodeEditor* codeEditor;
};

#endif // MAINWINDOW_H
