/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: mainwindow.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionTO92,SIGNAL(triggered()),this,SLOT(HandleAddTo92()));
    connect(ui->actionTO220,SIGNAL(triggered()),this,SLOT(HandleAddTo220()));
    connect(ui->actionAdd_PDIP,SIGNAL(triggered()),this,SLOT(HandleAddPDIP()));
    connect(ui->actionResistor,SIGNAL(triggered()),this,SLOT(HandleAddResistor()));
    ui->graphicsView->setScene(new QGraphicsScene());

    int rows = 19;
    int cols = 39;
    ui->graphicsView->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->graphicsView->scene()->setBackgroundBrush(Qt::black);
    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {
            ProtoPieceItem* item = new ProtoPieceItem();
            ui->graphicsView->scene()->addItem(item);
            item->setPos(col*20,row*20);
            this->ruudut.append(item);
        }
    }

  //  HandleAddTo92();
    HandleAddTo220();

    connect(ui->actionSave_board_as_PNG,SIGNAL(triggered()),this,SLOT(handleSaveAsPng()));
    connect(ui->actionPrint_Board,SIGNAL(triggered()),this,SLOT(handlePrint()));
    connect(ui->actionLoad_from_File,SIGNAL(triggered()),this,SLOT(handleLoadFromFile()));
    connect(ui->actionSave_to_File,SIGNAL(triggered()),this,SLOT(handleSaveToFile()));
}

void MainWindow::HandleAddResistor() {
    Resistor* resistor = new Resistor(4);
    ui->graphicsView->scene()->addItem(resistor);
    resistor->setZValue(10);
    resistor->setOpacity(0.6);
}

void MainWindow::HandleAddPDIP() {
    PDIP* pdip = new PDIP(8);
    ui->graphicsView->scene()->addItem(pdip);
    pdip->setOpacity(0.6);
    pdip->setZValue(10);
}

void MainWindow::HandleAddTo92() {
    To92* to92 = new To92();
    ui->graphicsView->scene()->addItem(to92);
    to92->setOpacity(0.6);
    to92->setZValue(10);
}

void MainWindow::HandleAddTo220() {
    To220* to220 = new To220();
    ui->graphicsView->scene()->addItem(to220);
    to220->setOpacity(0.6);
    to220->setZValue(10);
}

void MainWindow::handleSaveToFile() {
    QFile saveFile("export.sav");
    if (saveFile.open(QIODevice::WriteOnly)) {
        for (int idx=0; idx<this->ruudut.count(); idx++) {
            QString line = QString("%0\t%1\t%2\t%3\n").arg(idx).arg(this->ruudut.at(idx)->GetValue()).arg(this->ruudut.at(idx)->pos().x()).arg(this->ruudut.at(idx)->pos().y());
            saveFile.write(line.toAscii().data());
        }
        if (saveFile.isOpen()) {
            saveFile.close();
        }
    }
}

void MainWindow::handleLoadFromFile() {
    QFile loadFile("export.sav");

    if (loadFile.open(QIODevice::ReadOnly)) {
        QStringList lines = QString(loadFile.readAll()).split("\n");
        while (lines.empty()==false) {
            QString line = lines.takeFirst();
            if (line.trimmed().length()>0) {
                QStringList lineData = line.split("\t");
                int idx = QString(lineData.at(0)).toInt();
                ProtoPieceItem::PixmapType value = (ProtoPieceItem::PixmapType)QString(lineData.at(1)).toInt();
                ProtoPieceItem* item = this->ruudut.at(idx);
                item->SetValue(value);
                item->update();

            }
        }
    }

    if (loadFile.isOpen()) {
      loadFile.close();
    }
}

void MainWindow::handleSaveAsPng() {
    qDebug() << "save as png" << endl;
    QGraphicsScene* scene = ui->graphicsView->scene();

     QPixmap pixmap;
     QPainter painter(&pixmap);
     painter.setRenderHint(QPainter::Antialiasing);

     scene->render(&painter);

     pixmap.save("scene.png");
}

void MainWindow::handlePrint() {
    qDebug() << "print" << endl;
        QGraphicsScene* scene = ui->graphicsView->scene();
     QPrinter printer;
     if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
         QPainter painter(&printer);
         painter.setRenderHint(QPainter::Antialiasing);
         scene->render(&painter);
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}
