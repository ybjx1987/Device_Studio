#include "qbytearrayproperty.h"

QByteArrayProperty::QByteArrayProperty(QAbstractProperty* parent):
    QAbstractProperty(parent)
{
    setType("ByteArray");
    m_value = "";
}

QString QByteArrayProperty::getValueText()
{
    return getValue().toString();
}

QIcon QByteArrayProperty::getValueIcon()
{
    return QIcon();
}

