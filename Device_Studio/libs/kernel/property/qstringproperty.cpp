#include "qstringproperty.h"

#include "../qvarianttype.h"
#include "../xmlnode.h"

QStringProperty::QStringProperty(QAbstractProperty * parent):
    QAbstractProperty(parent),
    m_translation(false)
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
    if(m_uuid != uuid)
    {
        m_uuid = uuid;
        emit needUpdate();
    }
}

QString QStringProperty::getUuid()
{
    return m_uuid;
}

void QStringProperty::makeValue(XmlNode *xml)
{
    QAbstractProperty::makeValue(xml);
    m_uuid = xml->getProperty("uuid");
    m_translation = xml->getProperty("translation")=="true";
}

void QStringProperty::writeValue(XmlNode *xml)
{
    QAbstractProperty::writeValue(xml);
    xml->setProperty("uuid",m_uuid);
    xml->setProperty("translation",m_translation?"true":"false");
}

void QStringProperty::setTranslation(bool translation)
{
    if(m_translation != translation)
    {
        m_translation = translation;
        emit needUpdate();
    }
}

bool QStringProperty::getTranslation()
{
    return m_translation;
}
