#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->plainTextEditOriginal,SIGNAL(textChanged()),this,SLOT(HandleTextChanged()));

}

void MainWindow::HandleTextChanged() {
    QString original = ui->plainTextEditOriginal->toPlainText();
    QString convertFrom = "";
    QString convertTo = "";

    QCryptographicHash sha1(QCryptographicHash::Sha1);
    QCryptographicHash md4(QCryptographicHash::Md4);
    QCryptographicHash md5(QCryptographicHash::Md5);
    QScriptEngine jsengine;

    sha1.addData(original.toAscii());
    md4.addData(original.toAscii());
    md5.addData(original.toAscii());

    convertTo.append(QString("SHA1:\n%0\n\n").arg(QString(sha1.result().toHex())));
    convertTo.append(QString("MD4:\n%0\n\n").arg(QString(md4.result().toHex())));
    convertTo.append(QString("MD5:\n%0\n\n").arg(QString(md5.result().toHex())));
    convertTo.append(QString("Base64:\n%0\n\n").arg(QString(original.toAscii().toBase64())));
    convertTo.append(QString("Hex:\n%0\n\n").arg(QString(original.toAscii().toHex())));
    convertTo.append(QString("Percent Encoding:\n%0\n\n").arg(QString(original.toAscii().toPercentEncoding())));

    convertFrom.append(QString("Base64:\n%0\n\n").arg(QString(QByteArray::fromBase64(original.toAscii()))));
    convertFrom.append(QString("Hex:\n%0\n\n").arg(QString(QByteArray::fromHex(original.toAscii()))));
    convertFrom.append(QString("Percent Encoding:\n%0\n\n").arg(QString(QByteArray::fromPercentEncoding(original.toAscii()))));
    convertFrom.append(QString("JavaScript:\n%0\n\n").arg(jsengine.evaluate(original).toString()));

    ui->plainTextEditConvertTo->setPlainText(convertTo);
    ui->plainTextEditConvertFrom->setPlainText(convertFrom);

}

MainWindow::~MainWindow()
{
    delete ui;
}
