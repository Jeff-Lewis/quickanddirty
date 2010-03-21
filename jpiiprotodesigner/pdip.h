/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: pdip.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#ifndef PDIP_H
#define PDIP_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QAction>

class PDIP : public QGraphicsPixmapItem
{
public:
    PDIP(int pdip_size=8);
    void SetPDIPSize(int pdip_size);

protected slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event );
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);

protected:
    int pdip_size;
};


#endif // PDIP_H
