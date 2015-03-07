#include "qabstractsheetpropertyeditor.h"

#include "../../kernel/stylesheet/type/qabstractsheettype.h"

QAbstractSheetPropertyEditor::QAbstractSheetPropertyEditor(QAbstractSheetType * property,QWidget *parent) :
    QWidget(parent),
    m_property(property)
{
    connect(m_property,SIGNAL(valueChanged(QVariant)),
            this,SLOT(propertyChanged()));
}

QAbstractSheetPropertyEditor::~QAbstractSheetPropertyEditor()
{

}

void QAbstractSheetPropertyEditor::propertyChanged()
{

}
