#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T10:53:27
#
#-------------------------------------------------

QT       += core

TARGET = CPushButton
TEMPLATE = lib
CONFIG += staticlib


MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

SOURCES += \
    source/CPushButton.cpp

HEADERS += \
    ../include/CPushButton.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
