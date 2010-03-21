/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: pdip.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#include "pdip.h"

PDIP::PDIP(int pdip_size)
{
    SetPDIPSize(pdip_size);
    this->setFlag(QGraphicsItem::ItemIsMovable,true);
}

void PDIP::SetPDIPSize(int pdip_size) {
    this->pdip_size = pdip_size;
    int legsPerSide = (pdip_size/2);
    int height = legsPerSide*20;
    int width = 20*4;

    QPixmap pdipPixmap(width,height);
    pdipPixmap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pdipPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.setBrush(Qt::gray);
        painter.setPen(Qt::black);
    // lets draw the body
        painter.drawRect(15,0,width-30,height);//,Qt::gray);

    // lets draw the arc marking for #1 pin
        QRectF pinOne(0,0,20,20);
        painter.drawEllipse(30,-10,20,20);

    // lets draw the legs
        for (int idx=0; idx<legsPerSide; idx++) {
            painter.drawRect(10,8+20*idx,5,5);//,Qt::lightGray);
            painter.drawRect(width-15,8+20*idx,5,5);//,Qt::lightGray);
            // lets draw the numbers for the pins

            int id = idx+1;
            painter.drawText(15,20*idx,20,20,0,QString("%0").arg(legsPerSide+(legsPerSide-(id-1))));
            painter.drawText(width-30,20*idx,20,20,0,QString("%0").arg(id));
        }

    painter.end();
    this->setPixmap(pdipPixmap);
}

void PDIP::contextMenuEvent(QGraphicsSceneContextMenuEvent * event) {
     QMenu menu;
     QAction *rotateAction = menu.addAction("Rotate");
     QMenu *pdipSize = menu.addMenu("Change PDIP Size");
     QAction *size4 = pdipSize->addAction("4");
     QAction *size6 = pdipSize->addAction("6");
     QAction *size8 = pdipSize->addAction("8");
     QAction *size10 = pdipSize->addAction("10");
     QAction *size12 = pdipSize->addAction("12");
     QAction *size14 = pdipSize->addAction("14");
     QAction *size16 = pdipSize->addAction("16");
     QAction *size18 = pdipSize->addAction("18");
     QAction *size20 = pdipSize->addAction("20");
     QAction *size22 = pdipSize->addAction("22");
     QAction *size24 = pdipSize->addAction("24");
     QAction *size26 = pdipSize->addAction("26");
     QAction *size28 = pdipSize->addAction("28");
     QAction *size30 = pdipSize->addAction("30");
     QAction *size32 = pdipSize->addAction("32");
     QAction *size34 = pdipSize->addAction("34");
     QAction *size36 = pdipSize->addAction("36");
     QAction *size38 = pdipSize->addAction("38");
     QAction *size40 = pdipSize->addAction("40");
     QAction *selectedAction = menu.exec(event->screenPos());
     if (selectedAction==rotateAction) {
         this->rotate(90);
     } else if (selectedAction!=NULL) {
         bool ok;
         int pdipSize = selectedAction->text().toInt(&ok,10);
         if (ok) {
             this->SetPDIPSize(pdipSize);
         }
     }
}


void PDIP::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
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
