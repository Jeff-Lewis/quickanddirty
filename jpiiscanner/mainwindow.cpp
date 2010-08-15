#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << ">>" <<  __FUNCTION__;
        ui->setupUi(this);
                QString filename(QString("%0/%1").arg(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation)).arg(QString("scan-%0.pnm").arg(QDateTime::currentDateTime().toString("dd_MM_yyyy-hh_mm_ss"))));
        qDebug() << filename;
        processScan = new QProcess(this);
        scanApp = "/usr/bin/scanimage";
        connect(processScan,SIGNAL(finished(int)),this,SLOT(scanner_finished(int)));
        connect(processScan,SIGNAL(started()),this,SLOT(scanner_started()));
        enableScanUi();
        ui->labelScanning->setText("This might take several minutes. This phase depends on your scanner hardware as now the lamp is warmed and the image is scanned. So please be patient. :)\n\nThe scanned image will be placed on your Desktop.");
    qDebug() << "<<" <<  __FUNCTION__;
}

MainWindow::~MainWindow()
{
    qDebug() << ">>" <<  __FUNCTION__;
        delete ui;
    qDebug() << "<<" <<  __FUNCTION__;
}

void MainWindow::on_pushButtonScan_clicked()
{
    qDebug() << ">>" <<  __FUNCTION__;
        disableScanUi();
        QStringList args;
        args << "--resolution" << "300";
        this->processScan->start(scanApp,args);
    qDebug() << "<<" <<  __FUNCTION__;
}

void MainWindow::on_pushButtonStopScanning_clicked()
{
    qDebug() << ">>" <<  __FUNCTION__;
        enableScanUi();
        this->processScan->close();
    qDebug() << "<<" <<  __FUNCTION__;
}

void MainWindow::enableScanUi()
{
    qDebug() << ">>" <<  __FUNCTION__;
        ui->graphicsViewScan->setVisible(true);
        ui->pushButtonScan->setVisible(true);
        ui->pushButtonStopScanning->setVisible(false);
        ui->labelScanning->setVisible(false);
    qDebug() << "<<" <<  __FUNCTION__;
}

void MainWindow::disableScanUi()
{
    qDebug() << ">>" <<  __FUNCTION__;
        ui->graphicsViewScan->setVisible(false);
        ui->pushButtonScan->setVisible(false);
        ui->pushButtonStopScanning->setVisible(true);
        ui->labelScanning->setVisible(true);
    qDebug() << "<<" <<  __FUNCTION__;
}

void MainWindow::scanner_finished(int)
{
    qDebug() << ">>" <<  __FUNCTION__;
        enableScanUi();
        QByteArray scannedImageData = this->processScan->readAll();
        QPixmap scannedImage;
        QString filename(QString("%0/%1").arg(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation)).arg(QString("scan-%0.pnm").arg(QDateTime::currentDateTime().toString("dd_MM_yyyy-hh_mm_ss"))));
        QFile targetFile(filename);
        if (targetFile.open(QIODevice::WriteOnly))
        {
            targetFile.write(scannedImageData);
            targetFile.flush();
            targetFile.close();
            scannedImage.load(targetFile.fileName());
        } else {
            qWarning() << "Could not open file for writing!";
        }
        if (!ui->graphicsViewScan->scene()) {
            ui->graphicsViewScan->setScene(new QGraphicsScene());
        }
        ui->graphicsViewScan->scene()->addPixmap(scannedImage);
        scannedImage.save(QString("%0.png").arg(targetFile.fileName()));

        this->statusBar()->showMessage("Image Scanned Successfully!");
    qDebug() << "<<" <<  __FUNCTION__;
}

void MainWindow::scanner_started()
{
    qDebug() << ">>" <<  __FUNCTION__;
        disableScanUi();
        this->statusBar()->showMessage("Warming up the lamp / Scanning..");
    qDebug() << "<<" <<  __FUNCTION__;
}
