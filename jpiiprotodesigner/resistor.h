/*******************************************************************************
  Application name: jpiiProtoDesigner
  Filename: resistor.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
********************************************************************************/
#ifndef RESISTOR_H
#define RESISTOR_H

#include <QMenu>
#include <QAction>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class Resistor : public QGraphicsPixmapItem
{
public:
    Resistor(int size=4);
    void SetResistorSize(int size);

protected slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event );
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);
};

#endif // RESISTOR_H
