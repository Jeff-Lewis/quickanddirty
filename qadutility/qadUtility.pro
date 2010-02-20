# -------------------------------------------------
# Project created by QtCreator 2010-02-19T23:01:44
# -------------------------------------------------
TARGET = qadUtility
TEMPLATE = app
QT += script
SOURCES += main.cpp \
    mainwindow.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui
INCLUDEPATH += /usr/include
LIBPATH += botan \
    crypto \
    gmp \
    rt \
    z \
    bz2 \
    pthread
OTHER_FILES += gplv3-88x31.png \
    gpl-3.0.txt
RESOURCES += qadresources.qrc
