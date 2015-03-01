#include "qstylesheetgroup.h"

#include "qstylesheetitem.h"

#include "../xmlnode.h"

QStyleSheetGroup::QStyleSheetGroup(QObject *parent) : QObject(parent)
{

}

QStyleSheetGroup::~QStyleSheetGroup()
{

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
        if(!item->toXml(xml))
        {
            return false;
        }
    }
    return true;
}

bool QStyleSheetGroup::fromXml(XmlNode *xml)
{
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
