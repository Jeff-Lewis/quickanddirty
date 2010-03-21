# /*******************************************************************************
# Application name: jpiiAVR
# Author: Juhapekka Piiroinen
# License: GNU/GPLv3
# Description:
# This is a quick-and-dirty application for avrdude.
# (C) 2010 Juhapekka Piiroinen
# http://code.google.com/p/quickanddirty
# juhapekka.piiroinen@gmail.com
# *******************************************************************************/
TARGET = jpiiAVR
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    licensedialog.cpp \
    codeeditor.cpp \
    highlighter.cpp
HEADERS += mainwindow.h \
    licensedialog.h \
    codeeditor.h \
    highlighter.h \
    common.h
FORMS += mainwindow.ui \
    licensedialog.ui
OTHER_FILES += avrdevices.txt \
    programmer.txt \
    gplv3-88x31.png \
    gpl-3.0.txt \
    avrtargetboards_2.jpg \
    avrtargetboards_1.jpg \
    ATmega8-summary.pdf \
    2x3pin_ISP.png \
    atmega8.png \
    attiny-2313.gif
RESOURCES += jpiiavr.qrc

# http://doc.trolltech.com/qq/qq27-poppler.html
INCLUDEPATH += /usr/include/poppler/qt4
LIBS += -L/usr/lib \
    -lpoppler-qt4
