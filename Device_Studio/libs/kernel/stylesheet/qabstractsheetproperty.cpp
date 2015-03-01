#include "qabstractsheetproperty.h"

#include "../xmlnode.h"

QAbstractSheetProperty::QAbstractSheetProperty(QObject *parent) :
    QObject(parent),
    m_enabled(true)
{

}

QAbstractSheetProperty::~QAbstractSheetProperty()
{

}

void QAbstractSheetProperty::setName(const QString &name)
{
    m_name = name;
}

QString QAbstractSheetProperty::getName()
{
    return m_name;
}

void QAbstractSheetProperty::setShowName(const QString &showName)
{
    m_showName = showName;
}

QString QAbstractSheetProperty::getShowName()
{
    return m_showName;
}

void QAbstractSheetProperty::setEnabled(bool enabled)
{
    if(m_enabled != enabled)
    {
        m_enabled = enabled;
        emit enabledChanged(enabled);
    }
}

bool QAbstractSheetProperty::getEnabled()
{
    return m_enabled;
}

void QAbstractSheetProperty::setValue(const QVariant &value)
{
    if(!equal(value))
    {
        m_value = value;
        emit valueChanged(value);
    }
}

QVariant QAbstractSheetProperty::getValue()
{
    return m_value;
}

QString QAbstractSheetProperty::getValueText()
{
    return m_value.toString();
}

QString QAbstractSheetProperty::getStleSheet()
{
    QString ret;
    ret = m_name+":"+getValue().toString()+";";
    return ret;
}

bool QAbstractSheetProperty::equal(const QVariant &value)
{
    return m_value == value;
}

bool QAbstractSheetProperty::toXml(XmlNode *xml)
{
    xml->setTitle("Property");
    xml->setProperty("type",property("proName").toString());
    xml->setProperty("value",m_value.toString());
    xml->setProperty("enabled",m_enabled?"true":"false");
    return true;
}

bool QAbstractSheetProperty::fromXml(XmlNode *xml)
{
    m_enabled = xml->getProperty("enabled") =="true";
    m_value = xml->getProperty("value");
    return true;
}
