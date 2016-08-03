#-------------------------------------------------
#
# Project created by QtCreator 2015-08-14T13:59:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CMessageWidget
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

LIBS += -L./../lib -lCShadowWidget -lCPushButton -lCPixmapLabel
SOURCES +=\
    source/CMessageWidget.cpp

HEADERS  += \
    ../include/CMessageWidget.h

RESOURCES += \
    shadowrc.qrc
