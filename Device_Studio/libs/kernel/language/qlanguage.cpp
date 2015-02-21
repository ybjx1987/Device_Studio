#include "qlanguage.h"

#include "../xmlnode.h"

#include <QFile>
#include <QUuid>

QLanguage::QLanguage(const QString &id,
                     QObject *parent) : QObject(parent),
    m_id(id)
{
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
            || xml.getProperty("id") == "")
    {
        return false;
    }
    m_id = xml.getProperty("id");

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

void QLanguage::save(const QString &fileName)
{
    XmlNode xml;

    xml.setTitle("Language");
    xml.setProperty("id",m_id);

    foreach(QString str,m_keys)
    {
        XmlNode *obj = new XmlNode(&xml);
        obj->setTitle("Item");
        obj->setProperty("key",str);
        obj->setProperty("value",m_keyToValue.value(str));
    }

    QFile f(fileName);

    if(f.open(QFile::ReadWrite))
    {
        QString buffer;
        if(xml.save(buffer))
        {
            f.write(buffer.toLocal8Bit());
        }
        f.close();
    }
}

QString QLanguage::getID()
{
    return m_id;
}

void QLanguage::addItem(const QString &key, const QString &value)
{
    m_keys.append(key);
    m_keyToValue.insert(key,value);
    emit itemAdded(key);
}

void QLanguage::delItem(const QString &key)
{
    m_keys.removeAll(key);
    m_keyToValue.remove(key);
    emit itemDeled(key);
}

QStringList QLanguage::getKeys()
{
    return m_keys;
}

QString QLanguage::getValue(const QString &key)
{
    return m_keyToValue.value(key);
}

void QLanguage::setValue(const QString &key, const QString &value)
{
    if(!m_keys.contains(key))
    {
        addItem(key,value);
    }
    else
    {
        m_keyToValue.insert(key,value);
        emit itemUpdated(key);
    }
}
