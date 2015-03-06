#include "qstylesheetgroup.h"

#include "qstylesheetitem.h"

#include "../xmlnode.h"

#include <QFile>
#include <QVariant>
#include <QUuid>

QStyleSheetGroup::QStyleSheetGroup(QObject *parent) : QObject(parent)
{
    m_uuid = QUuid::createUuid().toString();
}

QStyleSheetGroup::~QStyleSheetGroup()
{
    clear();
}

QList<QStyleSheetItem*> QStyleSheetGroup::getItems()
{
    return m_items;
}

void QStyleSheetGroup::addItem(QStyleSheetItem *item)
{
    if(m_items.contains(item) || item->getUuid() == "")
    {
        return;
    }

    m_uuidToItem.insert(item->getUuid(),item);
    m_items.append(item);

    emit itemAdded(item);
}

void QStyleSheetGroup::delItem(QStyleSheetItem *item)
{
    if(!m_items.contains(item))
    {
        return;
    }

    emit itemDeled(item);
    m_uuidToItem.remove(item->getUuid());
    m_items.removeAll(item);
    delete item;
}

QStyleSheetItem* QStyleSheetGroup::getItem(const QString &uuid)
{
    return m_uuidToItem.value(uuid);
}

void QStyleSheetGroup::setName(const QString &name)
{
    m_name = name;
}

QString QStyleSheetGroup::getName()
{
    return m_name;
}

QString QStyleSheetGroup::getUuid()
{
    return m_uuid;
}

bool QStyleSheetGroup::toXml(XmlNode *xml)
{
    xml->setTitle("Group");
    xml->setProperty("name",m_name);
    xml->setProperty("uuid",m_uuid);

    foreach(QStyleSheetItem * item,m_items)
    {
        XmlNode * obj = new XmlNode(xml);
        if(!item->toXml(obj))
        {
            return false;
        }
    }
    return true;
}

bool QStyleSheetGroup::fromXml(XmlNode *xml)
{
    clear();
    if(xml->getTitle() == "Group")
    {
        return false;
    }

    m_name = xml->getProperty("name");
    m_uuid = xml->getProperty("uuid");

    if(m_name == "" || m_uuid == "")
    {
        return false;
    }

    foreach(XmlNode * obj,xml->getChildren())
    {
        if(obj->getTitle() == "Item")
        {
            QStyleSheetItem * item = new QStyleSheetItem;
            item->fromXml(obj);
            m_items.append(item);
            m_uuidToItem.insert(item->getUuid(),item);
        }
    }

    return true;
}

bool QStyleSheetGroup::load(const QString &filePath)
{
    setProperty("fileName","");
    QFile f(filePath);

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

    if(!fromXml(&xml))
    {
        setProperty("fileName",filePath);
        return false;
    }
    else
    {
        return true;
    }
}

bool QStyleSheetGroup::save(const QString & fileName)
{
    QFile f(fileName);

    if(!f.open(QFile::ReadWrite))
    {
        return false;
    }
    f.resize(0);

    XmlNode xml;

    if(!toXml(&xml))
    {
        return false;
    }

    QString buffer;

    if(!xml.save(buffer))
    {
        return false;
    }

    f.write(buffer.toLocal8Bit());

    f.close();

    return true;
}

void QStyleSheetGroup::clear()
{
    qDeleteAll(m_items);
    m_items.clear();
    m_uuidToItem.clear();
}
