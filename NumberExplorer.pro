#-------------------------------------------------
#
# Project created by QtCreator 2015-11-19T09:50:26
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumberExplorer
TEMPLATE = app


SOURCES += main.cpp\
    neconsolewindow.cpp \
    nemainwindow.cpp \
    neconsolecommand.cpp \
    neview.cpp \
    nedisplayobject.cpp \
    factormap.cpp \
    pointset.cpp

HEADERS  += \
    neconsolewindow.h \
    nemainwindow.h \
    neconsolecommand.h \
    neview.h \
    nedisplayobject.h \
    factormap.h \
    pointset.h

FORMS    +=

LIBS += -lgmp
