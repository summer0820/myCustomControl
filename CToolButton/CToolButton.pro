#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T10:43:46
#
#-------------------------------------------------

QT       += gui

TARGET = CToolButton
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

SOURCES += \
    source/CToolButton.cpp

HEADERS += \
    ../include/CToolButton.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
