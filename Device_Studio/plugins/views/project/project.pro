#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T21:40:26
#
#-------------------------------------------------

QT       += widgets

TARGET = project
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../../../../temp/bin/Device_Studio.app/Contents/MacOs/pages

LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lplatform

UI_DIR=../../../../temp/pages/project/ui
MOC_DIR=../../../../temp/pages/project/moc
OBJECTS_DIR=../../../../temp/pages/project/obj
RCC_DIR=../../../../temp/pages/project/rcc


unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    project.json

HEADERS += \
    qprojectplugin.h \
    qprojectwidget.h \
    qpageview.h \
    qpagepane.h

SOURCES += \
    qprojectplugin.cpp \
    qprojectwidget.cpp \
    qpageview.cpp \
    qpagepane.cpp
