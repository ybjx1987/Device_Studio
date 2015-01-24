QT       += core gui xml sql widgets
QT 	 += script

TARGET = corelib
TEMPLATE = lib

DESTDIR = ../../../temp/bin
DEFINES += CORE_LIBRARY


UI_DIR=../../../temp/libs/core/ui
MOC_DIR=../../../temp/libs/core/moc
OBJECTS_DIR=../../../temp/libs/core/obj
RCC_DIR=../../../temp/libs/core/rcc

HEADERS += \
    qabstractplugin.h \
    qdata.h \
    qhostfactory.h \
    version.h \
    xmlnode.h \
    pluginloader.h \
    host/qabstracthost.h \
    property/qabstractproperty.h

SOURCES += \
    qabstractplugin.cpp \
    qdata.cpp \
    qhostfactory.cpp \
    xmlnode.cpp \
    pluginloader.cpp \
    host/qabstracthost.cpp \
    property/qabstractproperty.cpp
