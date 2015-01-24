QT       += core gui widgets

TARGET = device_studio
TEMPLATE = app

DESTDIR = ../../temp/bin

LIBS += -L../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../temp/bin/Device_Studio.app/Contents/MacOS -lplatform

UI_DIR=../../temp/application/ui
MOC_DIR=../../temp/application/moc
OBJECTS_DIR=../../temp/application/obj
RCC_DIR=../../temp/application/rcc

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    fancyactionbar.cpp

HEADERS += \
    mainwindow.h \
    fancyactionbar.h
