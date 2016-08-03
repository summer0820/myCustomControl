#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T10:46:52
#
#-------------------------------------------------

QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CIPAddressEdit
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib

INCLUDEPATH += $$PWD/../include



SOURCES += \
    source/CIPAddressEdit.cpp \
    source/CIPPartlineEdit.cpp

HEADERS +=\
    CIPPartlineEdit.h \
    ../include/CIPAddressEdit.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
