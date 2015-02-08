#include "qfloatproperty.h"

QFloatProperty::QFloatProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{
    m_value = 0.0;
}

QString QFloatProperty::getValueText()
{
    return getValue().toString();
}

QIcon QFloatProperty::getValueIcon()
{
    return QIcon();
}
