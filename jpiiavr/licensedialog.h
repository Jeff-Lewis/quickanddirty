/*******************************************************************************
  Application name: jpiiAVR
  Filename: licensedialog.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/
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
