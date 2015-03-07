#include "qabstractstylesheetpropertyeditor.h"

QAbstractStyleSheetPropertyEditor::QAbstractStyleSheetPropertyEditor(
        QAbstractSheetType * property,QWidget *parent) :
    QWidget(parent),
    m_property(property)
{

}

QAbstractStyleSheetPropertyEditor::~QAbstractStyleSheetPropertyEditor()
{

}

