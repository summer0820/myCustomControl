#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T13:43:51
#
#-------------------------------------------------
TARGET = CMainWindow
TEMPLATE = lib
CONFIG += staticlib

MOC_DIR     = out/moc
OBJECTS_DIR = out/obj
DESTDIR  = $$PWD/../lib


INCLUDEPATH += $$PWD/../include

LIBS += -L./../lib -lCToolButton -lCPushButton -lCClickLabel


SOURCES += \
    source/CToolBar.cpp \
    source/CTitleBar.cpp \
    source/CStatusBar.cpp \
    source/CMainWindow.cpp \
    source/CDropShadowWidget.cpp

HEADERS +=\
    CToolBar.h \
    CTitleBar.h \
    CStatusBar.h \
    ../include/CDropShadowWidget.h \
    ../include/CMainWindow.h


#unix {
#   target.path = /usr/lib
#    INSTALLS += target
#}

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    icon/ID_STATES_TOOLBAR_hover.png \
    icon/ID_STATES_TOOLBAR.png \
    icon/ID_SOFTMANAGER_TOOLBAR.png \
    icon/ID_SETTING_TITLEBAR.png \
    icon/ID_MIN_TITLEBAR.png \
    icon/ID_LOGO_TOOLBAR.png \
    icon/ID_LICENSE_TOOLBAR.png \
    icon/ID_CLOSE_TITLEBAR_pressed.png \
    icon/ID_CLOSE_TITLEBAR_hover.png \
    icon/ID_CLOSE_TITLEBAR.png \
    icon/ID_BACKGROUND_TOOLBAR.jpg
