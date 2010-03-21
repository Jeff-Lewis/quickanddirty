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

#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QSettings>

#include <poppler-qt4.h>

#define AVRDUDE "/usr/bin/avrdude"

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

protected:
    void connectComponents();
    void fillComboboxes();
    void loadLicense();
    void loadHelp();

private:
    Ui::MainWindow *ui;
    QProcess* avrDude;
    QSettings settings;
    Poppler::Document *doc;
};

#endif // MAINWINDOW_H
