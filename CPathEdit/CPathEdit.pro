#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T14:04:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPathEdit
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

HEADERS += \
    ../include/CPathEdit.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    source/CPathEdit.cpp
