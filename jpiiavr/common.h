#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#define DIN qDebug() << ">>" << __FUNCTION__;
#define DOUT qDebug() << "<<" << __FUNCTION__;

#endif // COMMON_H
