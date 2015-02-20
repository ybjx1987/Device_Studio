#-------------------------------------------------
#
# Project created by QtCreator 2015-02-17T14:01:18
#
#-------------------------------------------------

QT       = core widgets gui

TARGET = language
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../../../../temp/bin/Device_Studio.app/Contents/MacOs/pages

LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../../../temp/bin/Device_Studio.app/Contents/MacOS -lplatform

UI_DIR=../../../../temp/pages/language/ui
MOC_DIR=../../../../temp/pages/language/moc
OBJECTS_DIR=../../../../temp/pages/language/obj
RCC_DIR=../../../../temp/pages/language/rcc

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    language.json \
    language.json

HEADERS += \
    qlanguageplugin.h \
    qlanguagewidget.h \
    qonelanguageview.h \
    qlanguagelist.h \
    qalllanguageview.h \
    qnewlanguagedialog.h \
    qdellanguagedialog.h \
    qnewitemdialog.h \
    qnewallitemdialog.h \
    qlanguageitemdeletegate.h

SOURCES += \
    qlanguageplugin.cpp \
    qlanguagewidget.cpp \
    qonelanguageview.cpp \
    qlanguagelist.cpp \
    qalllanguageview.cpp \
    qnewlanguagedialog.cpp \
    qdellanguagedialog.cpp \
    qnewitemdialog.cpp \
    qnewallitemdialog.cpp \
    qlanguageitemdeletegate.cpp

FORMS += \
    qnewlanguagedialog.ui \
    qdellanguagedialog.ui \
    qnewitemdialog.ui \
    qnewallitemdialog.ui
