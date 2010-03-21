#include "licensedialog.h"
#include "ui_licensedialog.h"

LicenseDialog::LicenseDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::LicenseDialog)
{
    m_ui->setupUi(this);
    loadLicense();
    this->setWindowFlags(Qt::Popup);
}

/********************************************************************************
  load application license
********************************************************************************/
void LicenseDialog::loadLicense() {
    QFile fileLicense(":/gpl-3.0.txt");
    QString license = "http://gplv3.fsf.org/";
    if (fileLicense.open(QIODevice::ReadOnly)) {
        license = QString(fileLicense.readAll());
    }
    m_ui->plainTextEditLicense->setPlainText(license);
}

LicenseDialog::~LicenseDialog()
{
    delete m_ui;
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
