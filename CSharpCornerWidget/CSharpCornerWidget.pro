#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T10:55:48
#
#-------------------------------------------------

TARGET = CSharpCornerWidget
TEMPLATE = lib
CONFIG += staticlib

DESTDIR  = $$PWD/../lib

LIBS += -L./../lib -lCShadowWidget

INCLUDEPATH += $$PWD/../include

SOURCES += \
    source/CCustomToolButton.cpp \
    source/CSharpCornerWidget.cpp

HEADERS += \
    CCustomToolButton.h \
    ../include/CSharpCornerWidget.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
