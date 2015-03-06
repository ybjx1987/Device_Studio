#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T21:40:26
#
#-------------------------------------------------

QT       += widgets

TARGET = stylesheet
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../../../../temp/bin/Device_Studio.app/Contents/MacOs/pages

LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lplatform

UI_DIR=../../../../temp/pages/stylesheet/ui
MOC_DIR=../../../../temp/pages/stylesheet/moc
OBJECTS_DIR=../../../../temp/pages/stylesheet/obj
RCC_DIR=../../../../temp/pages/stylesheet/rcc


unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    stylesheet.json

HEADERS += \
    qstylesheetplugin.h \
    qstylesheetwidget.h \
    qstylesheetgrouplistview.h \
    qdeletestylesheetdialog.h \
    qsingletitlewidget.h \
    qtitlewidget.h \
    qitemendwidget.h \
    qstylesheetitemwidget.h \
    qitempropertylistview.h \
    qonegroupwidget.h \
    qnewstylesheetgroupdialog.h

SOURCES += \
    qstylesheetplugin.cpp \
    qstylesheetwidget.cpp \
    qstylesheetgrouplistview.cpp \
    qdeletestylesheetdialog.cpp \
    qsingletitlewidget.cpp \
    qtitlewidget.cpp \
    qitemendwidget.cpp \
    qstylesheetitemwidget.cpp \
    qitempropertylistview.cpp \
    qonegroupwidget.cpp \
    qnewstylesheetgroupdialog.cpp

FORMS += \
    qdeletestylesheetdialog.ui \
    qnewstylesheetgroupdialog.ui
