#include "qlanguage.h"

#include "../xmlnode.h"

#include <QFile>

QLanguage::QLanguage(QLanguageManager *manager,const QString &id,
                     QObject *parent) :
    QObject(parent),
    m_id(id),
    m_languageManager(manager)
{
}

QLanguage::~QLanguage()
{

}

QString QLanguage::getID()
{
    return m_id;
}

void QLanguage::addItem(const QString &uuid, const QString &value)
{
    m_uuids.append(uuid);
    m_uuidToValue.insert(uuid,value);
    emit itemAdded(uuid);
}

void QLanguage::delItem(const QString &uuid)
{
    m_uuids.removeAll(uuid);
    m_uuidToValue.remove(uuid);
    emit itemDeled(uuid);
}

QStringList QLanguage::getUuids()
{
    return m_uuids;
}

QString QLanguage::getValue(const QString &uuid)
{
    return m_uuidToValue.value(uuid);
}

void QLanguage::setValue(const QString &uuid, const QString &value)
{
    m_uuidToValue.insert(uuid,value);
    emit itemUpdated(uuid);
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
    f.close();
    XmlNode xml;

    if(!xml.load(buffer))
    {
        return false;
    }

    if(xml.getTitle()!="Language")
    {
        return false;
    }

    m_id = xml.getProperty("id");

    if(m_id == "")
    {
        return false;
    }

    foreach(XmlNode * obj , xml.getChildren())
    {
        if(obj->getTitle() == "Item")
        {
            QString uuid = obj->getProperty("uuid");
            QString value = obj->getText();
            if(uuid != "")
            {
                addItem(uuid,value);
            }
        }
    }
    return true;
}

bool QLanguage::save(const QString &fileName)
{
    QFile f(fileName);

    if(!f.open(QFile::ReadWrite))
    {
        return false;
    }

    XmlNode xml;
    xml.setTitle("Language");
    xml.setProperty("id",m_id);

    foreach(QString str,m_uuids)
    {
        XmlNode * obj = new XmlNode(&xml);
        obj->setTitle("Item");
        obj->setProperty("uuid",str);
        obj->setText(m_uuidToValue.value(str));
    }

    QString buffer;
    if(!xml.save(buffer))
    {
        return false;
    }

    f.write(buffer.toLocal8Bit());

    return true;
}

QLanguageManager * QLanguage::getManager()
{
    return m_languageManager;
}
