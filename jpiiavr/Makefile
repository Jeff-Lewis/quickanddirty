#############################################################################
# Makefile for building: jpiiAVR
# Generated by qmake (2.01a) (Qt 4.5.2) on: Sat Apr 17 00:29:48 2010
# Project:  jpiiAVR.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile jpiiAVR.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I/usr/include/poppler/qt4 -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -L/usr/lib -lpoppler-qt4 -lQtGui -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		licensedialog.cpp \
		codeeditor.cpp \
		highlighter.cpp moc_mainwindow.cpp \
		moc_licensedialog.cpp \
		moc_codeeditor.cpp \
		moc_highlighter.cpp \
		qrc_jpiiavr.cpp
OBJECTS       = main.o \
		mainwindow.o \
		licensedialog.o \
		codeeditor.o \
		highlighter.o \
		moc_mainwindow.o \
		moc_licensedialog.o \
		moc_codeeditor.o \
		moc_highlighter.o \
		qrc_jpiiavr.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		jpiiAVR.pro
QMAKE_TARGET  = jpiiAVR
DESTDIR       = 
TARGET        = jpiiAVR

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_licensedialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: jpiiAVR.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile jpiiAVR.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile jpiiAVR.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/jpiiAVR1.0.0 || $(MKDIR) .tmp/jpiiAVR1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/jpiiAVR1.0.0/ && $(COPY_FILE) --parents mainwindow.h licensedialog.h codeeditor.h highlighter.h common.h .tmp/jpiiAVR1.0.0/ && $(COPY_FILE) --parents jpiiavr.qrc .tmp/jpiiAVR1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp licensedialog.cpp codeeditor.cpp highlighter.cpp .tmp/jpiiAVR1.0.0/ && $(COPY_FILE) --parents mainwindow.ui licensedialog.ui .tmp/jpiiAVR1.0.0/ && (cd `dirname .tmp/jpiiAVR1.0.0` && $(TAR) jpiiAVR1.0.0.tar jpiiAVR1.0.0 && $(COMPRESS) jpiiAVR1.0.0.tar) && $(MOVE) `dirname .tmp/jpiiAVR1.0.0`/jpiiAVR1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/jpiiAVR1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_licensedialog.cpp moc_codeeditor.cpp moc_highlighter.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_licensedialog.cpp moc_codeeditor.cpp moc_highlighter.cpp
moc_mainwindow.cpp: codeeditor.h \
		common.h \
		highlighter.h \
		licensedialog.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_licensedialog.cpp: common.h \
		licensedialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) licensedialog.h -o moc_licensedialog.cpp

moc_codeeditor.cpp: common.h \
		highlighter.h \
		codeeditor.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) codeeditor.h -o moc_codeeditor.cpp

moc_highlighter.cpp: common.h \
		highlighter.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) highlighter.h -o moc_highlighter.cpp

compiler_rcc_make_all: qrc_jpiiavr.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_jpiiavr.cpp
qrc_jpiiavr.cpp: jpiiavr.qrc \
		avrtargetboards_1.jpg \
		gplv3-88x31.png \
		avrdevices.txt \
		avrtargetboards_2.jpg \
		gpl-3.0.txt \
		programmer.txt
	/usr/bin/rcc -name jpiiavr jpiiavr.qrc -o qrc_jpiiavr.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_licensedialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_licensedialog.h
ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

ui_licensedialog.h: licensedialog.ui
	/usr/bin/uic-qt4 licensedialog.ui -o ui_licensedialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		codeeditor.h \
		common.h \
		highlighter.h \
		licensedialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		codeeditor.h \
		common.h \
		highlighter.h \
		licensedialog.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

licensedialog.o: licensedialog.cpp licensedialog.h \
		common.h \
		ui_licensedialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o licensedialog.o licensedialog.cpp

codeeditor.o: codeeditor.cpp codeeditor.h \
		common.h \
		highlighter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o codeeditor.o codeeditor.cpp

highlighter.o: highlighter.cpp highlighter.h \
		common.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o highlighter.o highlighter.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_licensedialog.o: moc_licensedialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_licensedialog.o moc_licensedialog.cpp

moc_codeeditor.o: moc_codeeditor.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_codeeditor.o moc_codeeditor.cpp

moc_highlighter.o: moc_highlighter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_highlighter.o moc_highlighter.cpp

qrc_jpiiavr.o: qrc_jpiiavr.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_jpiiavr.o qrc_jpiiavr.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

