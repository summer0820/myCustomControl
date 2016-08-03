#-------------------------------------------------
#
# Project created by QtCreator 2013-01-31T19:29:00
#
#-------------------------------------------------

QT       += core gui

TARGET = CShadowWidget
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

SOURCES += \
    source/CShadowWidget.cpp

HEADERS  += \
    ../include/CShadowWidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
