#include "qlanguage.h"

#include "../xmlnode.h"

#include <QFile>
#include <QUuid>

QLanguage::QLanguage(const QString &name,
                     const QString &icon,
                     QObject *parent) : QObject(parent),
    m_name(name),
    m_icon(icon)
{
    if(m_name == "")
    {
        m_uuid = QUuid::createUuid().toString();
    }
}

QLanguage::~QLanguage()
{

}

bool QLanguage::load(const QString &fileName)
{
    QFile f(fileName);

    if(!f.exists())
    {
        return false;
    }

    if(!f.open(QFile::ReadOnly))
    {
        return false;
    }

    QString buffer = f.readAll();

    XmlNode xml;

    if(!xml.load(buffer))
    {
        return false;
    }

    if(xml.getTitle() != "Language"
            || xml.getProperty("name") == "")
    {
        return false;
    }

    m_name = xml.getProperty("name");
    m_uuid = xml.getProperty("uuid");
    if(m_uuid == "")
    {
        m_uuid = QUuid::createUuid().toString();
    }

    foreach(XmlNode *obj,xml.getChildren())
    {
        if(obj->getTitle() == "Item")
        {
            m_keys.append(obj->getProperty("key"));
            m_keyToValue.insert(obj->getProperty("key"),
                                obj->getProperty("value"));
        }
    }

    return true;
}

QString QLanguage::getName()
{
    return m_name;
}

QString QLanguage::getUuid()
{
    return m_uuid;
}

QString QLanguage::getIcon()
{
    return m_icon;
}
