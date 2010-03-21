/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: resistor.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#include "resistor.h"

Resistor::Resistor(int size)
{
    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    SetResistorSize(size);
}

void Resistor::SetResistorSize(int size) {
    int width = size*20;
    int height = 1*20;
    QPixmap resistorPixmap(width,height);
    resistorPixmap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&resistorPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::black);

    // lets draw the body
    if (size<4) {
        painter.drawRect(5,0,width-10,height-1);//,Qt::gray);
    } else {
        painter.drawRect(20,0,width-40,height-1);//,Qt::gray);
    }

    // lets draw the legs
    painter.drawRect(10,8,10,5);//,Qt::lightGray);
    painter.drawRect(width-20,8,10,5);//,Qt::lightGray);

    this->setPixmap(resistorPixmap);
}

void Resistor::contextMenuEvent(QGraphicsSceneContextMenuEvent * event) {
     QMenu menu;
     QAction *rotateAction = menu.addAction("Rotate");
     QMenu *resSize = menu.addMenu("Change Resistor Size");
     QAction *size2 = resSize->addAction("2");
     QAction *size3 = resSize->addAction("3");
     QAction *size4 = resSize->addAction("4");
     QAction *size5 = resSize->addAction("5");
     QAction *size6 = resSize->addAction("6");
     QAction *selectedAction = menu.exec(event->screenPos());
     if (selectedAction==rotateAction) {
         this->rotate(90);
     }else if (selectedAction!=NULL) {
         bool ok;
         int size = selectedAction->text().toInt(&ok,10);
         if (ok) {
             this->SetResistorSize(size);
         }
     }
}

void Resistor::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseReleaseEvent(event);
    QPointF curpos = this->pos();
    int modX = ((int) curpos.x()) % 20;
    int modY = ((int) curpos.y()) % 20;
    if (modX!=0) {
        if (modX<10) {
            curpos.setX(curpos.x()-modX);
        } else {
            curpos.setX(curpos.x()+(20-modX));
        }
    }
    if (modY!=0) {
        if (modY<10) {
            curpos.setY(curpos.y()-modY);
        } else {
            curpos.setY(curpos.y()+(20-modY));
        }
    }

    this->setPos(curpos);

}
