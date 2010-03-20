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
//Filename: omasaunalahti.h
#ifndef OMASAUNALAHTI_H
#define OMASAUNALAHTI_H

#include <QRegExp>
#include <QTextStream>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QObject>
#include <QMessageBox>
#include <QUrl>
#include <QDate>
#include <QTime>

class OmaSaunalahti : public QObject
 {
     Q_OBJECT

public:
    OmaSaunalahti(QObject* parent=0);
    virtual ~OmaSaunalahti();

    void sendMessage(QNetworkAccessManager* manager, QString message);
    QString getSentMessageStatus() {return this->sentMessageStatus;}
    QString getSentMessages() {return this->sentMessages;}
    QString getSentMessages(QString htmlContent);
    QString getSentMessageStatus(QString htmlContent);
    void setSender(QString sender);
    void setReceiver(QString receiver);
    void setServer(QString server);
    void setUsername(QString username);
    void setPassword(QString password);
    QString getLastSentMessage();
    bool isLoggedIn();

public slots:
    void slotReadyRead();
    void showMessage(QString message);
    void slotError(QNetworkReply::NetworkError);
    void messageSent(QNetworkReply* reply);
    void replyFinished(QNetworkReply* reply);

signals:
    void processedUrl(QString);
    void messageSent();

protected:
    QString messageTime;
    bool loggedIn;
    QString sender;
    QString receiver;
    QString server;
    QString username;
    QString password;
    QString message;
    QString messageSuccess;
    QString sentMessageStatus;
    QString sentMessages;
};

#endif // OMASAUNALAHTI_H
