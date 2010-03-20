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
    mainwindow.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui
OTHER_FILES += avrdevices.txt \
    programmer.txt \
    gplv3-88x31.png \
    gpl-3.0.txt \
    avrtargetboards_2.jpg \
    avrtargetboards_1.jpg
RESOURCES += jpiiavr.qrc
