#include "qboolpropertyeditor.h"

#include "../../../kernel/property/qabstractproperty.h"

#include <QMouseEvent>

QBoolPropertyEditor::QBoolPropertyEditor(QAbstractProperty* property):
    QBasicEditor(property)
{

}

void QBoolPropertyEditor::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(m_property->getValue().toBool())
    {
        emit valueChanged(false);
    }
    else
    {
        emit valueChanged(true);
    }
}
