#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T15:42:49
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CMainFrame
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = $$PWD/../lib

INCLUDEPATH += $$PWD/../include


LIBS += -L./../lib -lCNavigationToolBar -lCSwitchPageToolBar -lCTreeWidget

SOURCES += \
    Source/CMainFrame.cpp

HEADERS  += \
    ../include/CMainFrame.h
