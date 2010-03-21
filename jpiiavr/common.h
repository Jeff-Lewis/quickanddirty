#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QDateTime>

#define DIN qDebug() << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << ">>" << __FILE__ << __LINE__ << __FUNCTION__;
#define DOUT qDebug() << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << "<<" << __FILE__ << __LINE__ << __FUNCTION__;

#endif // COMMON_H
