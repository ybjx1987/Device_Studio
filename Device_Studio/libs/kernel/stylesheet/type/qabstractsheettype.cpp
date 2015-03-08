#include "qabstractsheettype.h"

#include "../../xmlnode.h"

#include <QIcon>

QAbstractSheetType::QAbstractSheetType() :
    QObject(NULL),
    m_enabled(true)
{
}

QAbstractSheetType::~QAbstractSheetType()
{

}

void QAbstractSheetType::setName(const QString &name)
{
    m_name = name;
}

QString QAbstractSheetType::getName()
{
    return m_name;
}

void QAbstractSheetType::setEnabled(bool enabled)
{
    if(m_enabled != enabled)
    {
        m_enabled = enabled;
        emit enabledChanged(enabled);
    }
}

bool QAbstractSheetType::getEnabled()
{
    return m_enabled;
}

void QAbstractSheetType::setValue(const QVariant &value)
{
    if(!equal(value))
    {
        m_value = value;
        emit valueChanged(value);
        emit needUpdate();
    }
}

QVariant QAbstractSheetType::getValue()
{
    return m_value;
}

QString QAbstractSheetType::getValueText()
{
    return m_value.toString();
}

QIcon QAbstractSheetType::getValueIcon()
{
    return QIcon();
}

QString QAbstractSheetType::getStyleSheet()
{
    QString ret;
    ret = m_name+":"+getValueText();
    return ret;
}

bool QAbstractSheetType::equal(const QVariant &value)
{
    return m_value == value;
}

bool QAbstractSheetType::toXml(XmlNode *xml)
{
    xml->setTitle("Property");
    xml->setProperty("type",getName());
    xml->setProperty("value",m_value.toString());
    xml->setProperty("enabled",m_enabled?"true":"false");
    return true;
}

bool QAbstractSheetType::fromXml(XmlNode *xml)
{
    m_enabled = xml->getProperty("enabled") =="true";
    m_value = xml->getProperty("value");
    return true;
}
