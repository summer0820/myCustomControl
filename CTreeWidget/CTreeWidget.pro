#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T09:43:56
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTreeWidget
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

SOURCES += \
    Source/CFileSystemModel.cpp \
    Source/CFileSystemTreeWidget.cpp \
    Source/CPageTreeWidget.cpp \
    Source/CItemButton.cpp \
    Source/CPageTreeWidgetItem.cpp


HEADERS += \
    CFileSystemModel.h \
    ../include/CFileSystemTreeWidget.h \
    ../include/CPageTreeWidget.h \
    ../include/TItemStruct.h \
    CItemButton.h \
    CPageTreeWidgetItem.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
