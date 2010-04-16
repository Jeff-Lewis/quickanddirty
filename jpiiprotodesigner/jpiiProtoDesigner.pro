# /*******************************************************************************
# Application name: jpiiProtoDesigner
# Filename: jpiiProtoDesigner.pro
# Author: Juhapekka Piiroinen
# License: GNU/GPLv3
# Description:
# This is a quick-and-dirty application
# (C) 2010 Juhapekka Piiroinen
# http://code.google.com/p/quickanddirty
# juhapekka.piiroinen@gmail.com
# *******************************************************************************/
QT += network \
    webkit
TARGET = qadProtoDesigner
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    protopieceitem.cpp \
    pdip.cpp \
    resistor.cpp \
    to92.cpp \
    to220.cpp
HEADERS += mainwindow.h \
    protopieceitem.h \
    pdip.h \
    resistor.h \
    to92.h \
    to220.h
FORMS += mainwindow.ui
RESOURCES += 
