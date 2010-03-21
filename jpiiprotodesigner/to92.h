/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: to92.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#ifndef TO92_H
#define TO92_H

#include <QMenu>
#include <QAction>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class To92 : public QGraphicsPixmapItem
{
public:
    To92();

protected slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event );
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);

};

#endif // TO92_H
