/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: to220.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#ifndef TO220_H
#define TO220_H

#include <QMenu>
#include <QAction>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class To220 : public QGraphicsPixmapItem
{
public:
    To220();

protected slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event );
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);

};

#endif // TO220_H
