#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T11:14:36
#
#-------------------------------------------------

QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CClickLabel
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include


SOURCES += \
    source/CClickLabel.cpp

HEADERS += \
    ../include/CClickLabel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
