//! CSV Imported class
/*!
  \file csvimporter.cpp
  \author Juhapekka Piiroinen
  \date 31.3.2010
*/

#include "csvimporter.h"

CSVImporter::CSVImporter(QString databaseName, QString separator)
{
    DSTART;
        setColumnSeparator(separator);
        setSortByColumns(QList<int>());
        setSortAsc(true);
        setColumnCount(0);

        this->db = QSqlDatabase::addDatabase("QSQLITE");
        this->db.setDatabaseName(databaseName);

        if (this->db.open()==false)
        {
            DWARNING << "Could not open sqlite to memory";
            setInitialized(false);
            out << "Could not open SQLite database, please confirm that you have the Qt SQLite driver installed." << endl;
            QCoreApplication::exit(-1);
            return;
        }

        this->db.exec("CREATE TABLE csvtable(col0 INTEGER)");
        if (db.lastError().isValid())
        {
            DWARNING << db.lastError().text();
            return;
        }

        setInitialized(true);
    DEND;
}

CSVImporter::~CSVImporter()
{
    DSTART;
        if (this->db.isOpen())
        {
            if (this->db.driver()->hasFeature(QSqlDriver::Transactions))
            {
                this->db.commit();
            }
            this->db.close();
        }
    DEND;
}

bool CSVImporter::import(QByteArray data)
{
    DSTART;
        QStringList lines = QString(data).split(QLatin1Char('\n'));
        while (lines.empty()==false)
        {
            QString lineData = lines.takeFirst();

            // check if we have an empty line or not.
            if (lineData.trimmed().length()==0)
            {
                continue;
            }

            // do not trim the linedata as there can be empty fields at the left side
            QStringList rowData = lineData.split(QRegExp(columnSeparator()));
            QSqlQuery query;
            QString strCols;
            QString sql = "(";
            for (int iColumn=0; iColumn<rowData.count(); iColumn++)
            {
                sql += "?";
                strCols += QString("col%0").arg(iColumn);
                if (columnCount()<iColumn)
                {
                    increaseColumnCount();

                    QString strAlter = QString("ALTER TABLE csvtable ADD COLUMN col%0 INTEGER").arg(columnCount());
                    db.exec(strAlter);

                    if (db.lastError().isValid())
                    {
                        DWARNING << columnCount() << strAlter << db.lastError().text();
                    }

                }
                if (iColumn<rowData.count()-1)
                {
                    sql += ",";
                    strCols += ",";
                }
            } //---- for

            sql = QString("INSERT INTO csvtable(%0) VALUES %1").arg(strCols).arg(sql);
            sql += ")";

            query.prepare(sql);

            // fill prepared sql
            while (rowData.empty()==false)
            {
                query.addBindValue(rowData.takeFirst());
            } //---- while

            // execute sql and check if it failed
            if (query.exec()==false)
            {
                DWARNING << query.lastQuery() << "query failed" << query.lastError().text();
                DEND;
                return false;
            }
            this->db.commit();
        } //---- while
    DEND;
    return true;
}

bool CSVImporter::isValidSortColumns() {
    QList<int> sortCols = sortByColumns();
    if (sortCols.count()==0) {
        return false;
    }
    while (sortCols.empty()==false)
    {
        int sortCol = sortCols.takeFirst();
        if (sortCol>columnCount()) {
            DWARNING << "Invalid ";
            return false;
        }
    }
    return true;
}


QStringList CSVImporter::data(QString separator)
{
    DSTART;
        if (separator.isNull()) {
            separator = columnSeparator();
        }
        QStringList retval;
        QString strSql = QString("SELECT * FROM csvtable");
        if (sortByColumns().count()>0)
        {
            if (isValidSortColumns())
            {
                strSql += QString(" ORDER BY");
                QList<int> sortCols = sortByColumns();
                while (sortCols.empty()==false)
                {
                    strSql += QString(" col%0").arg(sortCols.takeFirst());
                    if (sortCols.count()>0)
                    {
                        strSql += ",";
                    }
                }
            } else {
               DWARNING << "Sort column value was too big. No such column.";
               out << "invalid sort column value. Maximum column number is " << columnCount() << "." << endl;
               return retval;
            }
        }
        strSql += QString(" %0").arg(isSortAsc()?"ASC":"DESC");

        QSqlQuery query = QSqlQuery(strSql);

        // execute sql
        if (query.exec()==false) {
            DWARNING << query.lastQuery() << query.lastError();
        }

        // go thru results and store them in to stringlist for return
        while (query.next())
        {
            QSqlRecord record = query.record();
            QString line;

            for (int idx=0; idx<record.count(); idx++)
            {
                line.append(record.value(idx).toString());
                line.append(separator);
            } //---- for
            retval << line;
        } //---- while
    DEND;
    return retval;
}
