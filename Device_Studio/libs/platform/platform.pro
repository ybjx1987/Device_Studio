QT       += core gui xml sql widgets

TARGET = platform
TEMPLATE = lib

DESTDIR = ../../../temp/bin/Device_Studio.app/Contents/MacOS
DEFINES += PLATFORM_LIBRARY

LIBS += -L../../../temp/bin/Device_Studio.app/Contents/MacOS -lkernel
LIBS += -L../../../temp/bin/Device_Studio.app/Contents/MacOS -lgradienteditor

unix {
    target.path = ../../../temp/bin/Device_Studio.app/Contents/MacOS
    INSTALLS += target
}

UI_DIR=../../../temp/libs/platform/ui
MOC_DIR=../../../temp/libs/platform/moc
OBJECTS_DIR=../../../temp/libs/platform/obj
RCC_DIR=../../../temp/libs/platform/rcc

HEADERS += \
    platformlibglobal.h \
    stylehelper.h \
    qsettingmanager.h \
    qplatformcore.h \
    styledbar.h \
    minisplitter.h \
    manhattanstyle.h \
    qbaseitemdelegate.h \
    qbaselistview.h \
    propertylist/qpropertylistview.h \
    propertylist/qpropertyeditorpane.h \
    qabstractpage.h \
    qabstractpagewidget.h \
    undocommand/qbaseundocommand.h \
    undocommand/qaddhostundocommand.h \
    qsoftcore.h \
    qsoftactionmap.h \
    qvalidatoredit.h \
    qactiontoolbar.h \
    qtoolbarbutton.h \
    propertylist/qpropertyeditorfactory.h \
    propertylist/editor/qbasiceditor.h \
    propertylist/editor/qabstractpropertyeditor.h \
    propertylist/editor/qboolpropertyeditor.h \
    undocommand/qpropertyeditundocommand.h \
    undocommand/qundocommandid.h \
    propertylist/editor/qbytearrayeditor.h \
    propertylist/editor/qintpropertyeditor.h \
    undocommand/qpropertyeditundocommandmore.h \
    qfancytabview.h \
    qfancytabviewwidget.h \
    propertylist/editor/qenumpropertyeditor.h \
    qlanguageid.h \
    qbuttonlineedit.h \
    qlineeditdialog.h \
    propertylist/editor/qbuttonpropertyeditor.h \
    propertylist/editor/qfontpropertyeditor.h \
    propertylist/editor/qstringpropertyeditor.h \
    propertylist/editor/qstringeditordialog.h \
    propertylist/editor/qfloatpropertyeditor.h \
    qabstractstylesheetpropertyeditor.h \
    stylesheet/qabstractsheetpropertyeditor.h \
    stylesheet/qsheettypeeditorfactory.h \
    stylesheet/qenumsheettypeeditor.h \
    stylesheet/qfontsheettypeeditor.h \
    stylesheet/qbrushsheettypeeditor.h \
    stylesheet/qbordersheettypeeditor.h \
    stylesheet/qnumbersheettypeeditor.h \
    qsystemresourcemanager.h \
    qrenamedialog.h \
    qprojectresourceview.h \
    stylesheet/qbrusheditor.h

SOURCES += \
    stylehelper.cpp \
    qsettingmanager.cpp \
    qplatformcore.cpp \
    styledbar.cpp \
    minisplitter.cpp \
    manhattanstyle.cpp \
    qbaseitemdelegate.cpp \
    qbaselistview.cpp \
    propertylist/qpropertylistview.cpp \
    propertylist/qpropertyeditorpane.cpp \
    qabstractpage.cpp \
    qabstractpagewidget.cpp \
    undocommand/qbaseundocommand.cpp \
    undocommand/qaddhostundocommand.cpp \
    qsoftcore.cpp \
    qsoftactionmap.cpp \
    qvalidatoredit.cpp \
    qactiontoolbar.cpp \
    qtoolbarbutton.cpp \
    propertylist/qpropertyeditorfactory.cpp \
    propertylist/editor/qbasiceditor.cpp \
    propertylist/editor/qabstractpropertyeditor.cpp \
    propertylist/editor/qboolpropertyeditor.cpp \
    undocommand/qpropertyeditundocommand.cpp \
    propertylist/editor/qbytearrayeditor.cpp \
    propertylist/editor/qintpropertyeditor.cpp \
    undocommand/qpropertyeditundocommandmore.cpp \
    qfancytabview.cpp \
    qfancytabviewwidget.cpp \
    propertylist/editor/qenumpropertyeditor.cpp \
    qlanguageid.cpp \
    qbuttonlineedit.cpp \
    qlineeditdialog.cpp \
    propertylist/editor/qbuttonpropertyeditor.cpp \
    propertylist/editor/qfontpropertyeditor.cpp \
    propertylist/editor/qstringpropertyeditor.cpp \
    propertylist/editor/qstringeditordialog.cpp \
    propertylist/editor/qfloatpropertyeditor.cpp \
    qabstractstylesheetpropertyeditor.cpp \
    stylesheet/qabstractsheetpropertyeditor.cpp \
    stylesheet/qsheettypeeditorfactory.cpp \
    stylesheet/qenumsheettypeeditor.cpp \
    stylesheet/qfontsheettypeeditor.cpp \
    stylesheet/qbrushsheettypeeditor.cpp \
    stylesheet/qbordersheettypeeditor.cpp \
    stylesheet/qnumbersheettypeeditor.cpp \
    qsystemresourcemanager.cpp \
    qrenamedialog.cpp \
    qprojectresourceview.cpp \
    stylesheet/qbrusheditor.cpp

RESOURCES += \
    platform.qrc

DISTFILES += \
    files/project/pages/form.pg \
    files/project/pages/page.list \
    files/project/languages/language.xml \
    files/project/languages/zh-CN.xml \
    files/project/languages/EN.xml \
    images/languages/translation.xml

FORMS += \
    qlineeditdialog.ui \
    propertylist/editor/qstringeditordialog.ui \
    qrenamedialog.ui
