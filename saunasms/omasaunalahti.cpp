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
//Filename: omasaunalahti.cpp
#include "omasaunalahti.h"

bool OmaSaunalahti::isLoggedIn() {
       return this->loggedIn;
}

void OmaSaunalahti::messageSent(QNetworkReply* reply) {
    emit messageSent();
}
void OmaSaunalahti::replyFinished(QNetworkReply* reply) {
    QByteArray data = reply->readAll();
    data = data.replace("\n","").replace("\r","").replace("\t","");
    this->sentMessageStatus = this->getSentMessageStatus(data);
    this->sentMessages = this->getSentMessages(data);
}

QString OmaSaunalahti::getLastSentMessage() {
    return QString("%0;%1;%2;%3;%4").arg(this->messageTime).arg(this->sender).arg(this->receiver).arg(this->message).arg(this->messageSuccess);
}

void OmaSaunalahti::sendMessage(QNetworkAccessManager* manager, QString message) {
    if (message.toAscii().length()==0)
        return;
    this->loggedIn = false;
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));

    this->message = message;
    this->messageTime = QString("%0 %1").arg(QDate::currentDate().toString("dd.MM.yyyy")).arg(QTime::currentTime().toString("hh:mm:ss.zzz"));
    QChar *messageChar = this->message.data();
    while (!messageChar->isNull()) {
        if (messageChar->isSpace()) {
               QString chr = QString("%0").arg(QString::number( messageChar->toAscii(), 16 ).toUpper());
               if (chr.length()==1)
                   chr = "%0" + chr;
               this->message = this->message.replace(messageChar->toAscii(),chr);
         }
        ++messageChar;
    }
    QUrl url = QUrl(this->server);
    url.addQueryItem("username",this->username);
    url.addQueryItem("login","Sisään");
    url.addQueryItem("password",this->password);

    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = manager->post(request,url.toString().split("?")[1].toAscii());

    url.setEncodedQuery(QByteArray());
    url.addQueryItem("sender",this->sender);
    url.addQueryItem("recipients",this->receiver);
    url.addQueryItem("text",this->message);
    url.addQueryItem("size",QString("%0").arg(this->message.toAscii().length()));
    url.addQueryItem("send","Lähetä");
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(messageSent(QNetworkReply*)));
    reply = manager->post(request,url.toString().split("?")[1].toAscii());
}


void OmaSaunalahti::slotError(QNetworkReply::NetworkError) {

}


void OmaSaunalahti::showMessage(QString message) {
 QMessageBox msgBox;
 msgBox.setText(message);
 msgBox.exec();
}

void OmaSaunalahti::slotReadyRead() {

}

QString OmaSaunalahti::getSentMessageStatus(QString htmlContent) {;
    QString retval = "???";
    if (htmlContent.indexOf("Viesti lähetetty.")!=-1) {
        retval = "onnistui.";
        this->messageSuccess = "1";
    } else if (htmlContent.indexOf("epäonnistui")!=-1) {
         retval = "epäonnistui!!!";
         this->messageSuccess = "0";
    }
    return retval;
}

QString OmaSaunalahti::getSentMessages(QString htmlContent) {
    QTextStream out(stdout);
    QString retval = QString();
    QString messageExpTxt = "<tr><td class=\"tdcontent1\">(.*)</td><td class=\"tdcontent1\">(.*)</td><td class=\"tdcontent1\">(.*)</td></tr>";
    QRegExp messageExp = QRegExp(messageExpTxt);
    QRegExp exp = QRegExp("<table cellpadding=\"7\" cellspacing=\"1\"><tr><td class=\"tdtitleheader\" colspan=\"3\">(.*)</td></tr><tr><td class=\"tdtitle\">(.*)</td><td class=\"tdtitle\">(.*)</td><td class=\"tdtitle\">(.*)</td></tr>("+messageExpTxt+")*");
    int pos = exp.indexIn(htmlContent,0);

    out << exp.cap(1) << endl;
    out << exp.cap(2) << endl;
    out << exp.cap(3) << endl;
    out << exp.cap(4) << endl;
    QString data = exp.cap(4);
    pos = 0;

    while ((pos = messageExp.indexIn(data,pos))!=-1) {
        out << messageExp.cap(1) << "\t" << messageExp.cap(2) << "\t" << messageExp.cap(3) << endl;
        retval += QString("%0;%1;%2\n").arg(messageExp.cap(1)).arg(messageExp.cap(2)).arg(messageExp.cap(3));
        pos += messageExp.matchedLength();
    }

    return retval;
}

void OmaSaunalahti::setSender(QString sender) {
    this->sender = sender;
}

void OmaSaunalahti::setReceiver(QString receiver) {
    this->receiver = receiver;
}

void OmaSaunalahti::setServer(QString server) {
    this->server = server;
}

void OmaSaunalahti::setUsername(QString username) {
    this->username = username;
}

void OmaSaunalahti::setPassword(QString password) {
    this->password = password;
}

OmaSaunalahti::~OmaSaunalahti() {

}
OmaSaunalahti::OmaSaunalahti(QObject* parent) : QObject(parent)
{
}
