#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T21:40:26
#
#-------------------------------------------------

QT       += widgets

TARGET = resource
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../../../../temp/bin/Device_Studio.app/Contents/MacOs/pages

LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lplatform

UI_DIR=../../../../temp/pages/resource/ui
MOC_DIR=../../../../temp/pages/resource/moc
OBJECTS_DIR=../../../../temp/pages/resource/obj
RCC_DIR=../../../../temp/pages/resource/rcc


unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    resource.json

HEADERS += \
    qresourceplugin.h \
    qresourcewidget.h \
    qresourcelistview.h \
    qaddresourcedialog.h \
    qsystemresourcedialog.h \
    qresourceitemwidget.h \
    qresourcerenamedialog.h \
    editor/qimageeditor.h \
    editor/qabstractfileeditor.h \
    editor/qeditorfactory.h

SOURCES += \
    qresourceplugin.cpp \
    qresourcewidget.cpp \
    qresourcelistview.cpp \
    qaddresourcedialog.cpp \
    qsystemresourcedialog.cpp \
    qresourceitemwidget.cpp \
    qresourcerenamedialog.cpp \
    editor/qimageeditor.cpp \
    editor/qabstractfileeditor.cpp \
    editor/qeditorfactory.cpp

FORMS += \
    qaddresourcedialog.ui \
    qsystemresourcedialog.ui \
    qresourcerenamedialog.ui
