#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T21:40:26
#
#-------------------------------------------------

QT       += widgets

TARGET = data
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../../../../temp/bin/Device_Studio.app/Contents/MacOs/pages

LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lplatform

UI_DIR=../../../../temp/pages/data/ui
MOC_DIR=../../../../temp/pages/data/moc
OBJECTS_DIR=../../../../temp/pages/data/obj
RCC_DIR=../../../../temp/pages/data/rcc


unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    data.json

HEADERS += \
    qdataplugin.h \
    qdatawidget.h \
    qdatalistview.h

SOURCES += \
    qdataplugin.cpp \
    qdatawidget.cpp \
    qdatalistview.cpp
