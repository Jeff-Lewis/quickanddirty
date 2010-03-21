/*******************************************************************************
  Application name: jpiiAVR
  Filename: licensedialog.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/
#include "licensedialog.h"
#include "ui_licensedialog.h"

LicenseDialog::LicenseDialog(QWidget *parent) : QDialog(parent), m_ui(new Ui::LicenseDialog)
{
    DIN
        m_ui->setupUi(this);
        loadLicense();
        this->setWindowFlags(Qt::Popup);
    DOUT
}

/********************************************************************************
  load application license
********************************************************************************/
void LicenseDialog::loadLicense()
{
    DIN
        QFile fileLicense(":/gpl-3.0.txt");
        QString license = "http://gplv3.fsf.org/";
        if (fileLicense.open(QIODevice::ReadOnly)) {
            license = QString(fileLicense.readAll());
        }
        m_ui->plainTextEditLicense->setPlainText(license);
    DOUT
}

LicenseDialog::~LicenseDialog()
{
    DIN
        delete m_ui;
    DOUT
}

void LicenseDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
