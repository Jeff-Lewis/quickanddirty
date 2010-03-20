//##############################################################################
//# This is a very quick and dirty SaunaSMS
//##############################################################################
//# This script will contact oma.saunalahti.fi and provides the sms service
//##############################################################################
//#    SaunaSMS is a small quick and dirty application which will provide a free
//#    sms service for Saunalahti (http://www.saunalahti.fi) customers.
//#
//#    Copyright (C) 2008-2009  Juhapekka Piiroinen
//#
//#    This program is free software: you can redistribute it and/or modify
//#    it under the terms of the GNU General Public License as published by
//#    the Free Software Foundation, either version 3 of the License, or
//#    (at your option) any later version.
//#
//#    This program is distributed in the hope that it will be useful,
//#    but WITHOUT ANY WARRANTY; without even the implied warranty of
//#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//#    GNU General Public License for more details.
//#
//#    You should have received a copy of the GNU General Public License
//#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//#############################################################################
//# Contact: juhapekka.piiroinen@gmail.com
//# Version: 2.0.0.1
//#############################################################################
//Filename: mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
#include <QMessageBox>
#include <QRegExp>
#include <QSettings>

#include "omasaunalahti.h"

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
    void updateText(QString);
    void replyFinished(QNetworkReply* reply);
    void sendMessage();
    void showMessage(QString message);
    void messageSent();
    void updateSMSLength();
    void clearSettings();

protected:
    OmaSaunalahti* omasaunalahti;

private:
    QSettings settings;
    Ui::MainWindow *ui;
    QString settingsPath;
};

#endif // MAINWINDOW_H
