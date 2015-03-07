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
    m_name = name;
}

QString QStyleSheetItemTitle::getName()
{
    return m_name;
}

void QStyleSheetItemTitle::setType(const QString &type)
{
    m_type = type;
}

QString QStyleSheetItemTitle::getType()
{
    return m_type;
}

void QStyleSheetItemTitle::setSubControl(const QString &subControl)
{
    m_subControl = subControl;
}

QString QStyleSheetItemTitle::getSubControl()
{
    return m_subControl;
}

void QStyleSheetItemTitle::setStates(const QStringList &states)
{
    m_states = states;
}

QStringList QStyleSheetItemTitle::getStates()
{
    return m_states;
}

bool QStyleSheetItemTitle::toXml(XmlNode *xml)
{
    xml->setTitle("Title");
    xml->setProperty("name",m_name);
    xml->setProperty("type",m_type);
    xml->setProperty("subcontrol",m_subControl);
    QString str = m_states.join(";");
    xml->setProperty("states",str);
    return true;
}

bool QStyleSheetItemTitle::fromXml(XmlNode *xml)
{
    if(xml->getTitle() != "Title")
    {
        return false;
    }

    m_name = xml->getProperty("name");
    m_type = xml->getProperty("type");
    m_subControl = xml->getProperty("subcontrol");
    m_states = xml->getProperty("states").split(";");
    return true;
}

bool QStyleSheetItemTitle::operator ==(const QStyleSheetItemTitle & title)
{
    return (m_name = title.m_name
            && m_type = title.m_type
            && m_subControl == title.m_subControl
            && m_states == title.m_states);
}

bool QStyleSheetItemTitle::operator !=(const QStyleSheetItemTitle & title)
{
    return !((*this)==title);
}
