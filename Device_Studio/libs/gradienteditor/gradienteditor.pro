#-------------------------------------------------
#
# Project created by QtCreator 2014-03-28T14:55:00
#
#-------------------------------------------------
QT       += widgets

TARGET = gradienteditor
TEMPLATE = lib
DESTDIR = ../../../temp/bin/Device_Studio.app/Contents/MacOS

UI_DIR=../../../temp/libs/kernel/ui
MOC_DIR=../../../temp/libs/kernel/moc
OBJECTS_DIR=../../../temp/libs/kernel/obj
RCC_DIR=../../../temp/libs/kernel/rcc

DEFINES += GRADIENTEDITOR_LIBRARY

SOURCES += \
    qtgradienteditor.cpp \
    qtgradientstopscontroller.cpp \
    qtgradientstopsmodel.cpp \
    qtcolorline.cpp \
    qtcolorbutton.cpp \
    qtgradientstopswidget.cpp \
    qtgradientwidget.cpp \
    qtgradientdialog.cpp

HEADERS +=\
        gradientEditor_global.h \
    qtgradienteditor.h \
    qtgradientstopscontroller.h \
    qtgradientstopsmodel.h \
    qtcolorline.h \
    qtcolorbutton.h \
    qtgradientstopswidget.h \
    qtgradientwidget.h \
    qtgradientdialog.h

FORMS += \
    qtgradienteditor.ui \
    qtgradientdialog.ui

RESOURCES += \
    gradienteditor.qrc

unix {
    target.path = ../../../temp/bin/Device_Studio.app/Contents/MacOS
    INSTALLS += target
}
