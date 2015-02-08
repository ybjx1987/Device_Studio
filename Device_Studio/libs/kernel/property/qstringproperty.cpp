#include "qstringproperty.h"

#include "../qvarianttype.h"
#include "../xmlnode.h"

QStringProperty::QStringProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{

}

QString QStringProperty::getValueText()
{
    return getValue().toString();
}

QIcon QStringProperty::getValueIcon()
{
    return QIcon();
}

void QStringProperty::setUuid(const QString &uuid)
{
    m_uuid = uuid;
}

void QStringProperty::makeValue(XmlNode *xml)
{
    QAbstractProperty::makeValue(xml);
    m_uuid = xml->getProperty("uuid");
}

void QStringProperty::writeValue(XmlNode *xml)
{
    QAbstractProperty::writeValue(xml);
    xml->setProperty("uuid",m_uuid);
}
