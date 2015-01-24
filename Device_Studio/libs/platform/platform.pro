QT       += core gui xml sql widgets

TARGET = platform
TEMPLATE = lib

DESTDIR = ../../../temp/bin/Device_Studio.app/Contents/MacOS
DEFINES += PLATFORM_LIBRARY

LIBS += -L../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel

UI_DIR=../../../temp/libs/platform/ui
MOC_DIR=../../../temp/libs/platform/moc
OBJECTS_DIR=../../../temp/libs/platform/obj
RCC_DIR=../../../temp/libs/platform/rcc

HEADERS += \
    platformlibglobal.h \
    stylehelper.h

SOURCES += \
    stylehelper.cpp
