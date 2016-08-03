#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T14:52:16
#
#-------------------------------------------------

QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CBusyIndicatorWidget
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    source/CBusyIndicatorWidget.cpp

HEADERS += \
    ../include/CBusyIndicatorWidget.h
