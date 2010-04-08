//! CSV Imported class
/*!
  \file csvimporter.h
  \author Juhapekka Piiroinen
  \date 31.3.2010
*/

#ifndef CSVIMPORTER_H
#define CSVIMPORTER_H

/////////////////////////////////////
// Qt Imports
/////////////////////////////////////
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QDebug>
#include <QCoreApplication>

/////////////////////////////////////
// project imports
/////////////////////////////////////
#include "common.h"

//! CSV File Importer
/*!
  This class imports csv information from QByteArray to Sqlite.
*/
class CSVImporter
{
public:

    //! constructor.
    /*!
      Initialize the importer to use memory only database and whitespace characters as a separator
      \param databaseName the database filename, default value is ':memory:'
      \param separator the column separator as regexp, default value is '\\s+'
      \param parent parent object, default value is '0'
    */
    CSVImporter(QString databaseName=":memory:", QString separator = "\\s+");

    //! deconstructor
    /*!
      checks if the database connection is open and if there are pending transactions,
      then it will close the connection.
    */
    ~CSVImporter();

    //! Import csv data into the sqlite
    /*!
      \param data the csv data which needs to be imported
      \return true if everything went fine, false otherwise
    */
    bool import(QByteArray data);

    //! sort and return the imported data
    /*!
      \return the imported data as QStringList
    */
    QStringList data(QString separator = 0);

    //! is class initialized and ready for usage
    bool    isInitialized()        { return this->bInitialized; }

    //! is ASC sorting enabled for the data()
    bool    isSortAsc()              { return this->bSortAsc; }
    void    setSortAsc(bool sortAsc) { this->bSortAsc = sortAsc; }

    //! how many columns were found during import
    int     columnCount()          { return this->iMaxCol; }

    //! which column to use for sorting in data()
    QList<int>  sortByColumns()        { return this->iSortColumns; }
    void    setSortByColumns(QList<int> columns) { this->iSortColumns = columns; }

    //! column detection regexp string
    QString columnSeparator()                     { return this->sSeparator; }
    void    setColumnSeparator(QString separator) { this->sSeparator = separator; }

protected:
    //! check if the given list of columns are valid
    bool    isValidSortColumns();

    //! set found column count
    void    setColumnCount(int colCount)     { this->iMaxCol = colCount; }

    //! increase column count by one
    void    increaseColumnCount()            { this->iMaxCol++; }

    //! set class initialization state
    void    setInitialized(bool initialized) { this->bInitialized = initialized; }


    QSqlDatabase db;                /**< the database connection inside the class */
    bool bInitialized;              /**< if database connection has been opened and prepared fine */
    bool bSortAsc;                  /**< if data is going to be sorted ASC, DESC if false */
    QString sSeparator;             /**< the regexp string for column detection */
    QList<int> iSortColumns;                /**< which column to use for sorting */
    int iMaxCol;                    /**< the maximum columns in a line found during importing */
};

#endif // CSVIMPORTER_H
