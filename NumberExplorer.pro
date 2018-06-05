#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T11:46:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumberExplorer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = src/precompiled_header.h
    CONFIG += precompile_header

*msvc* { # visual studio spec filter
      QMAKE_CXXFLAGS += -MP
  }

LIBS += "C:\development\mpir-3.0.0\dll\x64\Release\mpir.lib"

INCLUDEPATH += "C:\development\boost_1_65_1"
INCLUDEPATH += "C:\development\mpir-3.0.0\dll\x64\Release"

HEADERS += \
    src/factormap.h \
    src/neconsolecommand.h \
    src/neconsolewindow.h \
    src/nedisplayobject.h \
    src/nemainwindow.h \
    src/neview.h \
    src/pointset.h \
    src/precompiled_header.h \
    src/parabola.h \
    src/trigonometric.h

SOURCES += \
    src/consolecommands.cpp \
    src/factormap.cpp \
    src/main.cpp \
    src/neconsolecommand.cpp \
    src/neconsolewindow.cpp \
    src/nedisplayobject.cpp \
    src/nemainwindow.cpp \
    src/neview.cpp \
    src/pointset.cpp \
    src/parabola.cpp \
    src/trigonometric.cpp



