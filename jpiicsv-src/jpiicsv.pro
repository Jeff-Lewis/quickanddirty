# -------------------------------------------------
# Project created by QtCreator 2010-03-30T15:52:27
# -------------------------------------------------
QT += gui \
    sql
TARGET = jpiicsv
CONFIG += console
CONFIG -= app_bundle
CONFIG += staticlib
TEMPLATE = app
SOURCES += main.cpp \
    csvimporter.cpp
HEADERS += csvimporter.h \
    common.h
OTHER_FILES += NEWS \
    Makefile.am \
    INSTALL \
    data.csv \
    COPYING \
    configure.ac \
    ChangeLog \
    autogen.sh \
    AUTHORS \
    antigen.sh \
    README
