#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T16:13:46
#
#-------------------------------------------------

TARGET = CNavigationToolBar
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = $$PWD/../lib

INCLUDEPATH += $$PWD/../include

SOURCES += \
    Source/CLocationBar.cpp \
    Source/CNavigationToolBar.cpp \
    Source/CSearchWidget.cpp

HEADERS += \
    CLocationBar.h \
    CSearchWidget.h \
    ../include/CNavigationToolBar.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
