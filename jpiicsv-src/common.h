//! Common class and defines
/*!
  \file common.h
  \author Juhapekka Piiroinen
  \date 31.3.2010
*/

#ifndef COMMON_H
#define COMMON_H

/////////////////////////////////////
// Qt Imports
/////////////////////////////////////
#include <QDebug>
#include <QFile>
#include <QDateTime>


/*!
  DSTART, DEND, DWARNING and DOUT defines are used to minimize the amount of written code and copy
  paste. It also enables quick changes in the debug printing.
*/
#define DSTART qDebug() << ">>" << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz")<< __FILE__ << __LINE__ << __FUNCTION__
#define DEND qDebug() << "<<" << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << __FILE__ << __LINE__ << __FUNCTION__
#define DWARNING qWarning() << "/!\\" << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << __FILE__ << __LINE__ << __FUNCTION__
#define DOUT qDebug() << "-" << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << __FILE__ << __LINE__ << __FUNCTION__

//! for stdout messaging
static QTextStream out(stdout);

//! Common static stuff
/*!
  This class contains all the stuff which can be shared between all classes inside the application
*/
class Common {
public:
    //! Read file contents to QByteArray
    /*!
      if file can not be read, the function will return empty QByteArray and writes a message with DWARNING
         \param filename the name of the file
         \return the content of the file
    */
    static QByteArray readFileContents(QString filename)
    {
        DSTART;
            QFile file(filename);
            QByteArray data;
            if (file.exists() && file.open(QIODevice::ReadOnly))
            {
                data = file.readAll();
                file.close();
            }
            else
            {
                DWARNING << "Could not open file for reading";
            }
        DEND;
        return data;
    }


};



#endif // COMMON_H
