#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T08:28:09
#
#-------------------------------------------------

QT       += widgets script xml

TARGET = kernel
TEMPLATE = lib

DEFINES += KERNEL_LIBRARY

DESTDIR = ../../../temp/bin/Device_Studio.app/Contents/MacOS

UI_DIR=../../../temp/libs/kernel/ui
MOC_DIR=../../../temp/libs/kernel/moc
OBJECTS_DIR=../../../temp/libs/kernel/obj
RCC_DIR=../../../temp/libs/kernel/rcc

SOURCES += \
    xmlnode.cpp \
    host/qabstracthost.cpp \
    qproject.cpp \
    host/qprojecthost.cpp \
    property/qabstractproperty.cpp \
    host/qhostfactory.cpp \
    property/qbytearrayproperty.cpp \
    property/qintproperty.cpp \
    property/qboolproperty.cpp \
    property/qfloatproperty.cpp \
    property/qenumproperty.cpp \
    property/qalignmentproperty.cpp \
    host/qwidgethost.cpp \
    host/qabstractwidgethost.cpp \
    property/qrectproperty.cpp \
    property/qcursorproperty.cpp \
    qabstractplugin.cpp \
    pluginloader.cpp \
    host/qlineedithost.cpp \
    property/qmemerydataproperty.cpp \
    property/qfontproperty.cpp \
    property/qstringproperty.cpp \
    property/qscriptproperty.cpp \
    host/qframehost.cpp \
    host/qabstractbuttonhost.cpp \
    host/qpushbuttonhost.cpp \
    host/qcheckboxhost.cpp \
    host/qradiobuttonhost.cpp \
    host/qformhost.cpp \
    qhostsyncmanager.cpp \
    host/qcomboboxhost.cpp \
    language/qlanguagemanager.cpp \
    language/qlanguage.cpp \
    host/qabstractsliderhost.cpp \
    host/qdialhost.cpp \
    host/qsliderhost.cpp \
    host/qscrollbarhost.cpp \
    host/qlcdnumberhost.cpp \
    host/qlabelhost.cpp \
    host/qspinboxhost.cpp \
    host/qabstractspinboxhost.cpp \
    host/qdoublespinboxhost.cpp \
    host/qtimeedithost.cpp \
    property/qtimeproperty.cpp \
    property/qdateproperty.cpp \
    property/qdatetimeproperty.cpp \
    host/qdatehost.cpp \
    host/qdatetimeedithost.cpp \
    data/qabstractdatahost.cpp \
    data/qdatamanager.cpp \
    data/qdatagroup.cpp \
    data/qintdatahost.cpp \
    data/qfloatdatahost.cpp \
    stylesheet/qstylesheetmanager.cpp \
    stylesheet/qstylesheetgroup.cpp \
    stylesheet/qstylesheetitem.cpp \
    stylesheet/qabstractsheetproperty.cpp \
    stylesheet/qstylesheetitemtitle.cpp \
    stylesheet/qsheetpropertyfactory.cpp

HEADERS +=\
    xmlnode.h \
    kernellibglobal.h \
    host/qabstracthost.h \
    qproject.h \
    host/qprojecthost.h \
    property/qabstractproperty.h \
    host/qhostfactory.h \
    property/qbytearrayproperty.h \
    property/qintproperty.h \
    property/qboolproperty.h \
    property/qfloatproperty.h \
    property/qenumproperty.h \
    qvarianttype.h \
    property/qalignmentproperty.h \
    host/qwidgethost.h \
    host/qabstractwidgethost.h \
    property/qrectproperty.h \
    property/qcursorproperty.h \
    qabstractplugin.h \
    pluginloader.h \
    host/qlineedithost.h \
    property/qmemerydataproperty.h \
    property/qfontproperty.h \
    property/qstringproperty.h \
    property/qscriptproperty.h \
    host/qframehost.h \
    host/qabstractbuttonhost.h \
    host/qpushbuttonhost.h \
    host/qcheckboxhost.h \
    host/qradiobuttonhost.h \
    host/qformhost.h \
    qhostsyncmanager.h \
    host/qcomboboxhost.h \
    language/qlanguagemanager.h \
    language/qlanguage.h \
    host/qabstractsliderhost.h \
    host/qdialhost.h \
    host/qsliderhost.h \
    host/qscrollbarhost.h \
    host/qlcdnumberhost.h \
    host/qlabelhost.h \
    host/qspinboxhost.h \
    host/qabstractspinboxhost.h \
    host/qdoublespinboxhost.h \
    host/qtimeedithost.h \
    property/qtimeproperty.h \
    property/qdateproperty.h \
    property/qdatetimeproperty.h \
    host/qdatehost.h \
    host/qdatetimeedithost.h \
    data/qabstractdatahost.h \
    data/qdatamanager.h \
    data/qdatagroup.h \
    data/qintdatahost.h \
    data/qfloatdatahost.h \
    stylesheet/qstylesheetmanager.h \
    stylesheet/qstylesheetgroup.h \
    stylesheet/qstylesheetitem.h \
    stylesheet/qabstractsheetproperty.h \
    stylesheet/qstylesheetitemtitle.h \
    stylesheet/qsheetpropertyfactory.h

unix {
    target.path = ../../../temp/bin/Device_Studio.app/Contents/MacOS
    INSTALLS += target
}

OTHER_FILES +=
