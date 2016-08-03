#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T09:57:15
#
#-------------------------------------------------
QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPixmapLabel
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib
INCLUDEPATH += $$PWD/../include

HEADERS += \
    ../include/CPixmapLabel.h

SOURCES += \
    source/CPixmapLabel.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

