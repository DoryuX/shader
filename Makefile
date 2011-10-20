#############################################################################
# Makefile for building: build/cylinder
# Generated by qmake (2.01a) (Qt 4.7.4) on: Thu Oct 20 15:42:51 2011
# Project:  cylinder.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile cylinder.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -I. -I/usr/X11R6/include -Ibuild/moc
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L/usr/X11R6/lib64 -lGLEW -lQtOpenGL -lQtGui -lQtCore -lGLU -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/obj/

####### Files

SOURCES       = math/algebra3.cpp \
		shapes/cylinder.cpp \
		widgets/glwidget.cpp \
		main.cpp \
		widgets/mainwindow.cpp \
		shapes/sphere.cpp build/moc/moc_glwidget.cpp \
		build/moc/moc_mainwindow.cpp \
		build/rcc/qrc_resources.cpp
OBJECTS       = build/obj/algebra3.o \
		build/obj/cylinder.o \
		build/obj/glwidget.o \
		build/obj/main.o \
		build/obj/mainwindow.o \
		build/obj/sphere.o \
		build/obj/moc_glwidget.o \
		build/obj/moc_mainwindow.o \
		build/obj/qrc_resources.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		cylinder.pro
QMAKE_TARGET  = cylinder
DESTDIR       = build/
TARGET        = build/cylinder

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

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) build/ || $(MKDIR) build/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: cylinder.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile cylinder.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile cylinder.pro

dist: 
	@$(CHK_DIR_EXISTS) build/obj/cylinder1.0.0 || $(MKDIR) build/obj/cylinder1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) build/obj/cylinder1.0.0/ && $(COPY_FILE) --parents math/algebra3.h shapes/cylinder.h widgets/glwidget.h widgets/mainwindow.h shapes/sphere.h build/obj/cylinder1.0.0/ && $(COPY_FILE) --parents resources/resources.qrc build/obj/cylinder1.0.0/ && $(COPY_FILE) --parents math/algebra3.cpp shapes/cylinder.cpp widgets/glwidget.cpp main.cpp widgets/mainwindow.cpp shapes/sphere.cpp build/obj/cylinder1.0.0/ && (cd `dirname build/obj/cylinder1.0.0` && $(TAR) cylinder1.0.0.tar cylinder1.0.0 && $(COMPRESS) cylinder1.0.0.tar) && $(MOVE) `dirname build/obj/cylinder1.0.0`/cylinder1.0.0.tar.gz . && $(DEL_FILE) -r build/obj/cylinder1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: build/moc/moc_glwidget.cpp build/moc/moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) build/moc/moc_glwidget.cpp build/moc/moc_mainwindow.cpp
build/moc/moc_glwidget.cpp: shapes/cylinder.h \
		widgets/glwidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) widgets/glwidget.h -o build/moc/moc_glwidget.cpp

build/moc/moc_mainwindow.cpp: widgets/glwidget.h \
		shapes/cylinder.h \
		widgets/mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) widgets/mainwindow.h -o build/moc/moc_mainwindow.cpp

compiler_rcc_make_all: build/rcc/qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) build/rcc/qrc_resources.cpp
build/rcc/qrc_resources.cpp: resources/resources.qrc \
		images/numbers_bg.jpg \
		shaders/sphere.vert \
		shaders/cylinder.vert \
		shaders/sphere.frag \
		shaders/cylinder.frag \
		shaders/sphere2.vert \
		shaders/sphere2.frag
	/usr/bin/rcc -name resources resources/resources.qrc -o build/rcc/qrc_resources.cpp

compiler_image_collection_make_all: build/ui/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) build/ui/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

build/obj/algebra3.o: math/algebra3.cpp math/algebra3.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/algebra3.o math/algebra3.cpp

build/obj/cylinder.o: shapes/cylinder.cpp shapes/cylinder.h \
		math/algebra3.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/cylinder.o shapes/cylinder.cpp

build/obj/glwidget.o: widgets/glwidget.cpp widgets/glwidget.h \
		shapes/cylinder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/glwidget.o widgets/glwidget.cpp

build/obj/main.o: main.cpp widgets/mainwindow.h \
		widgets/glwidget.h \
		shapes/cylinder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/main.o main.cpp

build/obj/mainwindow.o: widgets/mainwindow.cpp widgets/mainwindow.h \
		widgets/glwidget.h \
		shapes/cylinder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/mainwindow.o widgets/mainwindow.cpp

build/obj/sphere.o: shapes/sphere.cpp shapes/sphere.h \
		math/algebra3.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/sphere.o shapes/sphere.cpp

build/obj/moc_glwidget.o: build/moc/moc_glwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/moc_glwidget.o build/moc/moc_glwidget.cpp

build/obj/moc_mainwindow.o: build/moc/moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/moc_mainwindow.o build/moc/moc_mainwindow.cpp

build/obj/qrc_resources.o: build/rcc/qrc_resources.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/obj/qrc_resources.o build/rcc/qrc_resources.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
