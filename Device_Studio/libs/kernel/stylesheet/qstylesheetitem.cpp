#include "qstylesheetitem.h"

#include "qstylesheetitemtitle.h"
#include "type/qabstractsheettype.h"
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

QList<QAbstractSheetType*> QStyleSheetItem::getPropertys()
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

    foreach(QAbstractSheetType * pro,m_propertys)
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
                delete t;
            }
            else
            {
                m_titles.append(t);
            }
        }
        else if(node->getTitle() == "Property")
        {
            QAbstractSheetType * pro = QSheetPropertyFactory::createProperty(
                        node->getProperty("type"));
            if(pro != NULL)
            {
                if(pro->fromXml(node))
                {
                    connect(pro,SIGNAL(needUpdate()),
                            this,SIGNAL(needUpdateStyleSheet()));
                    m_propertys.append(pro);
                }
                else
                {
                    delete pro;
                }
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
    emit needUpdateStyleSheet();
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
    emit needUpdateStyleSheet();
}

void QStyleSheetItem::addProperty(QAbstractSheetType *property)
{
    if(m_propertys.contains(property))
    {
        return;
    }

    m_propertys.append(property);
    connect(property,SIGNAL(needUpdate()),
            this,SIGNAL(needUpdateStyleSheet()));
    emit propertyAdded(property);
    emit needUpdateStyleSheet();
}

void QStyleSheetItem::delProperty(QAbstractSheetType *property)
{
    if(!m_propertys.contains(property))
    {
        return;
    }

    emit propertyDeled(property);
    m_propertys.removeAll(property);
    delete property;
    emit needUpdateStyleSheet();
}

void QStyleSheetItem::replaceProperty(QAbstractSheetType *oldPro, QAbstractSheetType *newPro)
{
    if(!m_propertys.contains(oldPro))
    {
        return;
    }

    m_propertys.replace(m_propertys.indexOf(oldPro),newPro);
    emit propertyReplaced(oldPro,newPro);
    connect(newPro,SIGNAL(needUpdate()),
            this,SIGNAL(needUpdateStyleSheet()));
    delete oldPro;
    emit needUpdateStyleSheet();
}

QString QStyleSheetItem::getUuid()
{
    return m_uuid;
}

QString QStyleSheetItem::getStyleSheet(const QString & title)
{
    QString ret = "";

    if(m_titles.size() == 0 || m_propertys.size() ==0)
    {
        return ret;
    }

    foreach(QStyleSheetItemTitle *t,m_titles)
    {
        QString temp;
        temp = (t->getType()=="By Name")?"#":"";
        temp+=t->getName();
        if(title == temp)
        {
            if(ret != "")
            {
                ret +=",";
            }
            ret += t->getText();
        }
    }

    if(ret == "")
    {
        return ret;
    }
    else
    {
        ret +="{\n";
    }
    QString buffer;
    foreach(QAbstractSheetType * property,m_propertys)
    {
        if(property->getEnabled())
        {
            QString str = property->getStyleSheet();
            if(str != "")
            {
                if(buffer != "")
                {
                    buffer += "\n";
                }
                buffer +=(str+";");
            }
        }
    }
    if(buffer == "")
    {
        return "";
    }
    ret += buffer;
    ret +="\n}";
    return ret;
}
