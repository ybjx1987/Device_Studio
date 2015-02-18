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
    qwidgetboxlist.cpp \
    formeditor/qformeditor.cpp \
    formeditor/qformpanel.cpp \
    formeditor/formresizer.cpp \
    formeditor/sizehandlerect.cpp \
    qdesignerdnditem.cpp \
    formeditor/qselectwidget.cpp \
    qhostlistview.cpp

HEADERS += qdesignerplugin.h \
    qdesignerwidget.h \
    qwidgetboxlist.h \
    formeditor/qformeditor.h \
    formeditor/qformpanel.h \
    formeditor/formresizer.h \
    formeditor/sizehandlerect.h \
    qdesignerdnditem.h \
    formeditor/qselectwidget.h \
    qhostlistview.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    designer.json

RESOURCES += \
    designer.qrc
