QT       += core gui xml sql widgets
QT 	 += script

TARGET = kernel
TEMPLATE = lib

DESTDIR = ../../../temp/bin/Device_Studio.app/Contents/MacOS
DEFINES += KERNEL_LIBRARY


UI_DIR=../../../temp/libs/kernel/ui
MOC_DIR=../../../temp/libs/kernel/moc
OBJECTS_DIR=../../../temp/libs/kernel/obj
RCC_DIR=../../../temp/libs/kernel/rcc

HEADERS += \
    qabstractplugin.h \
    qhostfactory.h \
    version.h \
    xmlnode.h \
    pluginloader.h \
    host/qabstracthost.h \
    property/qabstractproperty.h \
    kernellibglobal.h

SOURCES += \
    qabstractplugin.cpp \
    qhostfactory.cpp \
    xmlnode.cpp \
    pluginloader.cpp \
    host/qabstracthost.cpp \
    property/qabstractproperty.cpp
