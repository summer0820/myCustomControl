#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T09:58:46
#
#-------------------------------------------------


QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = CSortStandardItem
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib


HEADERS += \
    ../include/CSortStandardItem.h \
    pinyin1alpha.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    source/CSortStandardItem.cpp
