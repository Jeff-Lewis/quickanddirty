/*******************************************************************************
  Application name: jpiiAVR
  Filename: common.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/
#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QDateTime>

#define DIN qDebug() << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << ">>" << __FILE__ << __LINE__ << __FUNCTION__;
#define DOUT qDebug() << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << "<<" << __FILE__ << __LINE__ << __FUNCTION__;

#endif // COMMON_H
