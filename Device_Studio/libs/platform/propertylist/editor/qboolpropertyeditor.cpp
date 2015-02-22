#include "qboolpropertyeditor.h"

#include "../../../kernel/property/qabstractproperty.h"

#include <QMouseEvent>

QBoolPropertyEditor::QBoolPropertyEditor(QAbstractProperty* property):
    QBasicEditor(property)
{

}

void QBoolPropertyEditor::mouseReleaseEvent(QMouseEvent *)
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
