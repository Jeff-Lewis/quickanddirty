#ifndef LICENSEDIALOG_H
#define LICENSEDIALOG_H

#include <QtGui/QDialog>
#include <QFile>
#include "common.h"

namespace Ui {
    class LicenseDialog;
}

class LicenseDialog : public QDialog {
    Q_OBJECT
public:
    LicenseDialog(QWidget *parent = 0);
    ~LicenseDialog();

protected:
    void changeEvent(QEvent *e);
    void loadLicense();

private:
    Ui::LicenseDialog *m_ui;
};

#endif // LICENSEDIALOG_H
