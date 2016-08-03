#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T09:37:34
#
#-------------------------------------------------

QT       += widgets

QT       -= core

TARGET = CTableView
TEMPLATE = lib
MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib
CONFIG += staticlib
LIBS += -L./../lib -lCSortStandardItem -lCClickLabel

SOURCES += \
    source/CTableView.cpp \
    source/CHeaderView.cpp \
    source/CButtonDelegateStyle.cpp

HEADERS += \
    ../include/CTableView.h \
    CHeaderView.h \
    CButtonDelegateStyle.h

INCLUDEPATH += $$PWD/../include

unix {
    target.path = /usr/lib
    INSTALLS += target
}
