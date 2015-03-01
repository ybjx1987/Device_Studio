#include "qstylesheetitem.h"

#include "qstylesheetitemtitle.h"
#include "qabstractsheetproperty.h"
#include "qstylesheetitemtitle.h"
#include "qsheetpropertyfactory.h"

#include "../xmlnode.h"

#include <QUuid>

QStyleSheetItem::QStyleSheetItem(QObject *parent) :
    QObject(parent)
{
    m_uuid = QUuid::createUuid().toString();
}

QStyleSheetItem::~QStyleSheetItem()
{
    clear();
}

QList<QAbstractSheetProperty*> QStyleSheetItem::getPropertys()
{
    return m_propertys;
}

QList<QStyleSheetItemTitle*> QStyleSheetItem::getTitles()
{
    return m_titles;
}

bool QStyleSheetItem::toXml(XmlNode *xml)
{
    xml->setTitle("Item");
    xml->setProperty("uuid",m_uuid);
    foreach(QStyleSheetItemTitle* title,m_titles)
    {
        XmlNode *obj = new XmlNode(xml);
        obj->setTitle("Title");
        if(!title->toXml(obj))
        {
            return false;
        }
    }

    foreach(QAbstractSheetProperty * pro,m_propertys)
    {
        XmlNode * obj = new XmlNode(xml);
        obj->setTitle("Property");
        if(!pro->toXml(obj))
        {
            return false;
        }
    }

    return true;
}

bool QStyleSheetItem::fromXml(XmlNode *xml)
{
    if(xml->getTitle() != "Item")
    {
        return false;
    }

    m_uuid = xml->getProperty("uuid");
    if(m_uuid == "")
    {
        m_uuid = QUuid::createUuid().toString();
    }

    QList<XmlNode*> list = xml->getChildren();

    foreach(XmlNode * node,list)
    {
        if(node->getTitle() == "Title")
        {
            QStyleSheetItemTitle *t = new QStyleSheetItemTitle;
            if(!t->fromXml(node))
            {
                clear();
                return false;
            }
            m_titles.append(t);
        }
        else if(node->getTitle() == "Property")
        {
            QAbstractSheetProperty * pro = QSheetPropertyFactory::createProperty(
                        node->getProperty("proName"));
            if(pro != NULL)
            {
                pro->fromXml(node);
            }
        }
    }

    return true;
}

void QStyleSheetItem::clear()
{
    qDeleteAll(m_titles);
    qDeleteAll(m_propertys);
    m_titles.clear();
    m_propertys.clear();
}

void QStyleSheetItem::addTitle(QStyleSheetItemTitle *title)
{
    if(m_titles.contains(title))
    {
        return;
    }

    m_titles.append(title);

    emit titleAdded(title);
}

void QStyleSheetItem::delTitle(QStyleSheetItemTitle *title)
{
    if(!m_titles.contains(title))
    {
        return;
    }
    emit titleDeled(title);
    m_titles.removeAll(title);
    delete title;
}

void QStyleSheetItem::addProperty(QAbstractSheetProperty *property)
{
    if(m_propertys.contains(property))
    {
        return;
    }

    m_propertys.append(property);
    emit propertyAdded(property);
}

void QStyleSheetItem::delProperty(QAbstractSheetProperty *property)
{
    if(!m_propertys.contains(property))
    {
        return;
    }

    emit propertyDeled(property);
    m_propertys.removeAll(property);
    delete property;
}

QString QStyleSheetItem::getUuid()
{
    return m_uuid;
}
