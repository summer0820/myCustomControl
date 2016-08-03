#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T15:57:53
#
#-------------------------------------------------

TARGET = CSwitchPageToolBar
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = $$PWD/../lib


INCLUDEPATH += $$PWD/../include

SOURCES += Source/CSwitchPageToolBar.cpp

HEADERS += \
    ../include/CSwitchPageToolBar.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
