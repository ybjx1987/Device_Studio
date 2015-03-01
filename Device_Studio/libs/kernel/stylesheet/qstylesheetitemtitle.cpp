#include "qstylesheetitemtitle.h"

#include "../xmlnode.h"

QStyleSheetItemTitle::QStyleSheetItemTitle(QObject *parent) : QObject(parent)
{

}

QStyleSheetItemTitle::~QStyleSheetItemTitle()
{

}

void QStyleSheetItemTitle::setName(const QString &name)
{
    if(m_name != name)
    {
        m_name = name;
        emit propertyChanged("name");
    }
}

QString QStyleSheetItemTitle::getName()
{
    return m_name;
}

void QStyleSheetItemTitle::setType(const QString &type)
{
    if(m_type != type)
    {
        m_type = type;
        emit propertyChanged("type");
    }
}

QString QStyleSheetItemTitle::getType()
{
    return m_type;
}

void QStyleSheetItemTitle::setEnabled(bool enabled)
{
    if(m_enabled != enabled)
    {
        m_enabled = enabled;
        emit propertyChanged("enabled");
    }
}

bool QStyleSheetItemTitle::getEnabled()
{
    return m_enabled;
}

bool QStyleSheetItemTitle::toXml(XmlNode *xml)
{
    xml->setTitle("Title");
    xml->setProperty("name",m_name);
    xml->setProperty("enabled",m_enabled?"true":"false");
    xml->setProperty("type",m_type);
    return true;
}

bool QStyleSheetItemTitle::fromXml(XmlNode *xml)
{
    if(xml->getTitle() != "Title")
    {
        return false;
    }

    m_name = xml->getProperty("name");
    m_enabled = xml->getProperty("enabled")=="true";
    m_type = xml->getProperty("type");
    return true;
}
