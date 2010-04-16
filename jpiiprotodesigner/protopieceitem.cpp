/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: protopieceitem.cpp
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#include "protopieceitem.h"

ProtoPieceItem::ProtoPieceItem()
{
    if (reika_m.isNull()) {
        reika_m = QPixmap(20,20);
        QPainter painterReika(&reika_m);
        painterReika.fillRect(0,0,20,20,Qt::red);
        painterReika.fillRect(5,5,10,10,Qt::black);
        painterReika.setPen(Qt::black);
        painterReika.drawLine(0,0,20,0);
        painterReika.drawLine(0,19,20,19);
        painterReika.end();
    }
    if (katkos.isNull()) {
        katkos = QPixmap(20,20);
        QPainter painterKatkos(&katkos);
        painterKatkos.fillRect(0,0,20,20,Qt::black);
        painterKatkos.fillRect(0,1,20,18,Qt::red);
        painterKatkos.fillRect(5,0,10,20,Qt::black);
        painterKatkos.end();
    }
    setPixmap(reika_m);
    value = REIKA;
}


void ProtoPieceItem::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
    rotatePixmap();
}

void ProtoPieceItem::SetValue(PixmapType value) {
    this->value = value;
    if (value==REIKA) {
        setPixmap(reika_m);
    } else {
        setPixmap(katkos);
    }
    this->update();

}

void ProtoPieceItem::rotatePixmap() {
    if (value==KATKOS) {
        setPixmap(reika_m);
        value = REIKA;
    } else {
        setPixmap(katkos);
        value = KATKOS;
    }
    this->update();
}
