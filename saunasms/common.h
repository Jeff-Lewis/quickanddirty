#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QDateTime>

#define __MAEMO_DEV_WIN32__ 1

#define DMSG    qDebug() << QString("[%0] %1:%2::%3 - ").arg(QDateTime::currentDateTime().toString("dd.mm.yyyy hh:MM:ss.zzz")).arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).toAscii().data()
#define DSTART  qDebug() << QString("[%0] >> %1:%2::%3").arg(QDateTime::currentDateTime().toString("dd.mm.yyyy hh:MM:ss.zzz")).arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).toAscii().data()
#define DEND    qDebug() << QString("[%0] << %1:%2::%3").arg(QDateTime::currentDateTime().toString("dd.mm.yyyy hh:MM:ss.zzz")).arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).toAscii().data()

#endif // COMMON_H
