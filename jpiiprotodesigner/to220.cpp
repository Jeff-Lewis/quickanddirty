/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: to220.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#include "to220.h"

To220::To220()
{
    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    int size = 3;
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
        painter.drawRect(5,0,width-10,height);//,Qt::gray);
    } else {
        painter.drawRect(20,0,width-40,height);//,Qt::gray);
    }

    // lets draw the legs
    painter.drawRect(10,8,10,5);//,Qt::lightGray);
    painter.drawRect(width/2-2,8,5,5);//,Qt::lightGray);
    painter.drawRect(width-20,8,10,5);//,Qt::lightGray);

    // lets draw the heat absorber
    painter.drawRect(5,height-5,width-10,height);//,Qt::lightGray);

    painter.setPen(Qt::black);
    painter.drawText(10,-2,10,10,0,"1");
    painter.drawText(25,-2,10,10,0,"2");
    painter.drawText(40,-2,10,10,0,"3");

    this->setPixmap(resistorPixmap);
}

void To220::contextMenuEvent(QGraphicsSceneContextMenuEvent * event) {
     QMenu menu;
     QAction *rotateAction = menu.addAction("Rotate");
     QAction *selectedAction = menu.exec(event->screenPos());
     if (selectedAction==rotateAction) {
         this->rotate(90);
     }
}


void To220::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
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
