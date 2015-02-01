#-------------------------------------------------
#
# Project created by QtCreator 2015-02-01T13:07:23
#
#-------------------------------------------------

QT       = core widgets gui

TARGET = designer
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../../../../temp/bin/Device_Studio.app/Contents/MacOs/pages

LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lplatform

UI_DIR=../../../../temp/pages/designer/ui
MOC_DIR=../../../../temp/pages/designer/moc
OBJECTS_DIR=../../../../temp/pages/designer/obj
RCC_DIR=../../../../temp/pages/designer/rcc

SOURCES += qdesignerplugin.cpp \
    qdesignerwidget.cpp \
    qwidgetboxlist.cpp

HEADERS += qdesignerplugin.h \
    qdesignerwidget.h \
    qwidgetboxlist.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    designer.json
