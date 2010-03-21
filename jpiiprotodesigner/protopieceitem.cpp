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
    setPixmap(QPixmap(":/reika_m.BMP"));
    value = REIKA;
}


void ProtoPieceItem::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
    rotatePixmap();
}

void ProtoPieceItem::SetValue(PixmapType value) {
    this->value = value;
    if (value==REIKA) {
        setPixmap(QPixmap(":/reika_m.BMP"));
    } else {
        setPixmap(QPixmap(":/katkos.BMP"));
    }
    this->update();

}

void ProtoPieceItem::rotatePixmap() {
    if (value==KATKOS) {
        setPixmap(QPixmap(":/reika_m.BMP"));
        value = REIKA;
    } else {
        setPixmap(QPixmap(":/katkos.BMP"));
        value = KATKOS;
    }
    this->update();
}
