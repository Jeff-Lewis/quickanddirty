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
//Filename: mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->omasaunalahti = new OmaSaunalahti();
    ui->senderLineEdit->setText(this->settings.value("Sender/text").toString());
    ui->receiverLineEdit->setText(this->settings.value("Receiver/text").toString());
    ui->messagePlainTextEdit->setPlainText(this->settings.value("Message/text").toString());
    ui->usernameLineEdit->setText(this->settings.value("Username/text").toString());
    ui->passwordLineEdit->setText(this->settings.value("Password/text").toString());
    ui->savePasswordCheckBox->setChecked(this->settings.value("Save Password On Exit/text").toBool());
    QString server = this->settings.value("Server/text","https://oma.saunalahti.fi").toString();
    if (server.length()==0)
        server = "https://oma.saunalahti.fi";
    ui->serverLineEdit->setText(server);
    QString serverPath = this->settings.value("Server Path/text","/settings/smsSend").toString();
    if (serverPath.length()==0)
        serverPath = "/settings/smsSend";
    ui->serverPathLineEdit->setText(serverPath);
    ui->sentMessagesTextEdit->setPlainText(this->settings.value("Sent Messages/text","").toString());
    connect(this->omasaunalahti,SIGNAL(messageSent()),this,SLOT(messageSent()));
    connect(ui->messagePlainTextEdit,SIGNAL(textChanged()),this,SLOT(updateSMSLength()));
    connect(ui->clearAllSettingsPushButton,SIGNAL(clicked()),this,SLOT(clearSettings()));
    connect(ui->sendPushButton,SIGNAL(clicked()),SLOT(sendMessage()));
}

void MainWindow::clearSettings() {
    ui->senderLineEdit->setText("");
    ui->receiverLineEdit->setText("");
    ui->messagePlainTextEdit->setPlainText("");
    ui->usernameLineEdit->setText("");
    ui->passwordLineEdit->setText("");
    ui->serverLineEdit->setText("");
    ui->serverPathLineEdit->setText("");
    ui->sentMessagesTextEdit->setPlainText("");
    this->settings.clear();
}

void MainWindow::updateSMSLength() {
    ui->charsLeftLineEdit->setText(QString("%0").arg(160-(ui->messagePlainTextEdit->toPlainText().length())));
}

void MainWindow::messageSent() {
    QString sentMessage = this->omasaunalahti->getLastSentMessage();
    if (ui->sentMessagesTextEdit->toPlainText().indexOf(sentMessage)==-1)
        ui->sentMessagesTextEdit->append(sentMessage);
    this->statusBar()->showMessage("Viestin lähetys "+this->omasaunalahti->getSentMessageStatus());
}

void MainWindow::updateText(QString text) {

}


void MainWindow::showMessage(QString message) {
 QMessageBox msgBox;
 msgBox.setText(message);
 msgBox.exec();
}


void MainWindow::replyFinished(QNetworkReply* reply) {
    QByteArray data = reply->readAll();
    data = data.replace("\n","").replace("\r","").replace("\t","");
    QString sentMessageStatus = this->omasaunalahti->getSentMessageStatus(data);
    QString sentMessages = this->omasaunalahti->getSentMessages(data);
    if (this->omasaunalahti->isLoggedIn()) {
        this->showMessage(sentMessages);
        this->showMessage(sentMessageStatus);
        this->statusBar()->showMessage("Viesti lähetetty!");
    }
}


void MainWindow::sendMessage() {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QString sender = ui->senderLineEdit->text();
    QString receiver = ui->receiverLineEdit->text();
    QString message = ui->messagePlainTextEdit->toPlainText();
    QString server = QString("%0%1").arg(ui->serverLineEdit->text()).arg(ui->serverPathLineEdit->text());
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    this->omasaunalahti->setSender(sender);
    this->omasaunalahti->setReceiver(receiver);
    this->omasaunalahti->setServer(server);
    this->omasaunalahti->setUsername(username);
    this->omasaunalahti->setPassword(password);
    this->omasaunalahti->sendMessage(manager,message);
    this->statusBar()->showMessage("Lähetetään viestiä..");

}

MainWindow::~MainWindow()
{
    this->settings.setValue("Save Password On Exit/text", ui->savePasswordCheckBox->isChecked());
    this->settings.setValue("Sender/text", ui->senderLineEdit->text());
    this->settings.setValue("Receiver/text", ui->receiverLineEdit->text());
    this->settings.setValue("Message/text", ui->messagePlainTextEdit->toPlainText());
    this->settings.setValue("Username/text", ui->usernameLineEdit->text());
    if (ui->savePasswordCheckBox->isChecked())
        this->settings.setValue("Password/text", ui->passwordLineEdit->text());
    else
        this->settings.setValue("Password/text", "");
    this->settings.setValue("Server/text", ui->serverLineEdit->text());
    this->settings.setValue("Server Path/text", ui->serverPathLineEdit->text());
    this->settings.setValue("Sent Messages/text",ui->sentMessagesTextEdit->toPlainText());
    delete ui;
}
