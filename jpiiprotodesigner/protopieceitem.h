/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: protopieceitem.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#ifndef PROTOPIECEITEM_H
#define PROTOPIECEITEM_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class ProtoPieceItem : public QGraphicsPixmapItem
{
public:
    enum PixmapType {
        REIKA,
        KATKOS
    };
    ProtoPieceItem();

    int GetValue() { return this->value; }
    void SetValue(PixmapType value);

protected slots:
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    void rotatePixmap();

protected:
    QPixmap reika_m;
    QPixmap katkos;

    PixmapType value;
};

#endif // PROTOPIECEITEM_H
