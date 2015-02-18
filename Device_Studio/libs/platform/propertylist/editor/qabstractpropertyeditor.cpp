#include "qabstractpropertyeditor.h"

#include "../../../kernel/property/qabstractproperty.h"

QAbstractPropertyEditor::QAbstractPropertyEditor(QAbstractProperty* property,
                                                 QWidget* parent) :
    QWidget(parent),
    m_property(property)
{
    setProperty("no-ManhattanStyle",true);
    connect(property,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(propertyValueChanged()));
}

QAbstractPropertyEditor::~QAbstractPropertyEditor()
{

}

void QAbstractPropertyEditor::propertyValueChanged()
{

}
