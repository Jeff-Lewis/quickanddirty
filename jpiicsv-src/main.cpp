//! Main class of the jpiiCSV parser.
/*!
  The purpose of this application is to convert CSV file or to import it into a database

  REQUIREMENTS:
        libqt4-dev
        libqt4-sql-sqlite
        + autoconf

  BUILD INSTRUCTIONS FOR LINUX:
        ./autogen.sh
        ./configure
        make
        make install        

  USAGE EXAMPLE:
        jpiicsv --filename=testdata.txt --sort-desc --sort-column=0,3,20,11,1 --out-separator=,
  OR
        cat testdata.txt | jpiicsv --sort-asc --out-separator=. --sort-column=1

  \file main.cpp
  \author Juhapekka Piiroinen
  \date 31.3.2010
*/
/////////////////////////////////////
// Qt imports
/////////////////////////////////////
#include <QtCore/QCoreApplication>
#include <QVariant>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlResult>
#include <QTextStream>
#include <QMutexLocker>
#include <QMutex>
#include <QCoreApplication>
#include <QApplication>

/////////////////////////////////////
// project imports
/////////////////////////////////////
#include "csvimporter.h"
#include "common.h"


//! lock for debug message handler, as we write to file
static QMutex message_handler_lock;

//! debug message handler
void message_handler(QtMsgType type, const char *msg) {
    QMutexLocker lock(&message_handler_lock);
    QString fileName = QString("%0//%1").arg(QApplication::applicationDirPath()).arg("debug.log");
    QFile* logFile = new QFile(fileName);
    if (logFile->open(QIODevice::Append|QIODevice::Text|QIODevice::Unbuffered)) {
        QString m = QString(msg).trimmed();
        logFile->write(QString("%0\n").arg(m).toAscii());
        logFile->close();
    }
    logFile->deleteLater();
}

//! main
/*!
  parse commandline parameters and then call the external classes to do all the work
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInstallMsgHandler(message_handler);

    DSTART;
        QString sRegExp_SortColumns = "--sort-column=[0-9,]+";
        QString sRegExp_Separator = "--separator=\\S+";
        QString sRegExp_DatabaseName = "--sqlite=\\S+";
        QString sRegExp_Filename = "--filename=\\S+";
        QString sRegExp_OutSeparator = "--out-separator=\\S+";
        QString sRegExp_Pipe = "--pipe";

        QString sUsage = "\n  jpiicsv - CSV file to something-else utility\n\n"
                         "\t== Command Line Arguments and Example ====================\n\n"

                         "\tSeparators:\n\n"
                         "\t\t--out-separator=\\S+\t\t(default is comma)\n"
                         "\t\t--separator=\\S+\t\t\t(default is \\s+)\n"
                         "\t\t--sqlite=filename.sqlite\t(default is none)\n\n"

                         "\tSorting:\n\n"
                         "\t\t--sort-column=[0-9,]+\t\t(default is none)\n"
                         "\t\t--sort-asc\t\t\t(default)\n"
                         "\t\t--sort-desc\n\n"

                         "\tInput Selection:\n\n"
                         "\t\t--filename=data.csv\t\t(default is none)\n"
                         "\t\t--pipe\n\n"

                         "\tExample:\n\n"
                         "\t\tjpiicsv --filename=import.csv --sort-column=1,3\n"
                         "\t\tcat import.csv | jpiicsv --pipe\n\n"
                         "\t==========================================================\n\n"
                         "  (C) 2010 Juhapekka Piiroinen - GNU/GPLv3\n"
                         "           juhapekka.piiroinen@gmail.com\n"
                         "           http://code.google.com/p/quickanddirty";

        QList<int> iSortColumns;
        bool bSortAsc = true;
        QString databaseName = ":memory:";
        QString sSeparator = "\\s+";
        QString sOutSeparator = ",";

        /*!
          Check for commandline arguments which can change default values
         */

        QStringList arguments = a.arguments();

        //! lets check if the user wants to sort DESC rather than ASC
        if (arguments.contains("--sort-desc",Qt::CaseInsensitive))
        {
            bSortAsc = false;
        } //--- if sort desc

        //! lets check if user wants to sort columns by something else than first column
        if (arguments.indexOf(QRegExp(sRegExp_SortColumns))!=-1)
        {
            int idx = arguments.indexOf(QRegExp(sRegExp_SortColumns));
            if (arguments.count()>=idx) {
                bool ok = false;
                QString value = arguments.at(idx).split("=").takeLast();
                QStringList values = value.split(",");
                while (values.empty()==false)
                {
                    int value = values.takeFirst().toInt(&ok);
                    if (ok) {
                        iSortColumns.append(value);
                    }
                }
            } //--- if arg count>=idx
        } //--- if sort column

        //! lets check if the user has changed the column separator to something else
        if (arguments.indexOf(QRegExp(sRegExp_Separator))!=-1)
        {
            int idx = arguments.indexOf(QRegExp(sRegExp_Separator));
            if (arguments.count()>=idx) {
                QStringList argument = arguments.at(idx).split("=");
                argument.takeFirst();
                sSeparator = argument.join("=");
            }
        }

        //! lets check if the user has defined database name
        if (arguments.indexOf(QRegExp(sRegExp_DatabaseName))!=-1)
        {
            int idx = arguments.indexOf(QRegExp(sRegExp_DatabaseName));
            if (arguments.count()>=idx) {
                QStringList argument = arguments.at(idx).split("=");
                argument.takeFirst();
                databaseName = argument.join("=");
            }
        }

        //! lets check if the user has defined output column separator name
        if (arguments.indexOf(QRegExp(sRegExp_OutSeparator))!=-1)
        {
            int idx = arguments.indexOf(QRegExp(sRegExp_OutSeparator));
            if (arguments.count()>=idx) {
                QStringList argument = arguments.at(idx).split("=");
                argument.takeFirst();
                sOutSeparator = argument.join("=");
            }
        }

        // lets read the file content
        QByteArray fileData;

        //! lets check if the user has defined filename for importing
        if (arguments.indexOf(QRegExp(sRegExp_Filename))!=-1)
        {
            int idx = arguments.indexOf(QRegExp(sRegExp_Filename));
            if (arguments.count()>=idx) {
                QStringList argument = arguments.at(idx).split("=");
                argument.takeFirst();
                fileData = Common::readFileContents(argument.join("="));
            }
        } else if (arguments.indexOf(QRegExp(sRegExp_Pipe))!=-1) {
            QTextStream sText(stdin,QIODevice::ReadOnly);
            fileData = sText.readAll().toAscii();
        } else {
           // not used, lets show usage later
        }

        // lets check if there was something
        if (fileData.length()>0) {

            // there was so lets import it and check if it will work
            CSVImporter importer(databaseName,sSeparator);
            importer.setSortByColumns(iSortColumns);
            importer.setSortAsc(bSortAsc);

            if (importer.import(fileData)==false)
            {
                DWARNING << "import failed";
            }
            else
            {
                // check if we were using memory only database
                if (databaseName==":memory:") {
                    // import went fine so lets show what we got
                    QStringList lines = importer.data(sOutSeparator);
                    while (lines.count()>0)
                    {
                        out << lines.takeFirst().toAscii().data() << endl;
                    } //--- while
                }

            } //--- if import
        }
        else
        {
            out << sUsage.toAscii().data() << endl;

        }//--- if length>0

    DEND;
    ///////////////////////////////////////
    // no need to stay here.. move along..
    // -- add this if otherwise - return a.exec();
    return 0;
}
