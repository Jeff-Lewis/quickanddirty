//##############################################################################
//# This is a very quick and dirty SaunaSMS
//##############################################################################
//# This script will contact oma.saunalahti.fi and provides the sms service
//##############################################################################
//#    SaunaSMS is a small quick and dirty application which will provide a free
//#    sms service for Saunalahti (http://www.saunalahti.fi) customers.
//#
//#    Copyright (C) 2008-2009  Juhapekka Piiroinen
//#
//#    This program is free software: you can redistribute it and/or modify
//#    it under the terms of the GNU General Public License as published by
//#    the Free Software Foundation, either version 3 of the License, or
//#    (at your option) any later version.
//#
//#    This program is distributed in the hope that it will be useful,
//#    but WITHOUT ANY WARRANTY; without even the implied warranty of
//#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//#    GNU General Public License for more details.
//#
//#    You should have received a copy of the GNU General Public License
//#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//#############################################################################
//# Contact: juhapekka.piiroinen@gmail.com
//# Version: 2.0.0.1
//#############################################################################
//Filename: main.cpp

#include <QtGui/QApplication>
#include <QDebug>
#include "common.h"
#include "mainwindow.h"
#include "mainwindowmaemo.h"
#include "omasaunalahti.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Juhapekka Piiroinen");
    QCoreApplication::setOrganizationDomain("jpii.fi");
    QCoreApplication::setApplicationName("SaunaSMS");

////////////////////////////////////////////////////////////////////
// check which version we are running
    DMSG << "Lets check which version we are running";
#ifdef __WIN32__
    DMSG << "__WIN32__ defined";
  #ifdef __MAEMO_DEV_WIN32__
    DMSG << "__MAEMO_DEV_WIN32__ defined";
    MainWindowMaemo w;
  #else
    DMSG << "__MAEMO_DEV_WIN32__ is not defined";
    MainWindow w;
  #endif
#else
    DMSG << "__WIN32__ is not defined";
    MainWindowMaemo w;
#endif
////////////////////////////////////////////////////////////////////

    DMSG << "lets display the main window";
    w.show();

    return a.exec();
}
