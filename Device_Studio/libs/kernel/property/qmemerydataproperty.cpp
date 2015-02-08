#include "qmemerydataproperty.h"

#include "../qvarianttype.h"
#include "../xmlnode.h"

QMemeryDataProperty::QMemeryDataProperty(QAbstractProperty* parent):
    QAbstractProperty(parent)
{
}

QString QMemeryDataProperty::getValueText()
{
    MemeryValueItems c=getValue().value<MemeryValueItems>();
    if(c.size()==0)
    {
        return "None";
    }
    else
    {
        return QString("count:%1").arg(c.size());
    }
}

QIcon QMemeryDataProperty::getValueIcon()
{
    return QIcon();
}

bool QMemeryDataProperty::equal(const QVariant &value)
{
    MemeryValueItems  items1 = getValue().value<MemeryValueItems>();
    MemeryValueItems  items2 = value.value<MemeryValueItems>();

    if(items1.size() != items2.size())
    {
        return false;
    }

    int count = items1.size();
    for(int i = 0 ; i < count ; i++)
    {
        if(items1.at(i) != items2.at(i))
        {
            return false;
        }
    }
    return true;
}

bool QMemeryDataProperty::toXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }
    xml->clear();
    xml->setTitle(PROPERTY_TITLE);
    xml->setProperty("name",getName());


    MemeryValueItems  items = getValue().value<MemeryValueItems>();
    XmlNode * node;
    foreach(tagMemeryValueInfo info,items)
    {
        node = new XmlNode(xml);
        node->setTitle("Item");
        node->setProperty("propertyName",info.m_propertyName);
        node->setProperty("dataUuid",info.m_dataUuid);
    }

    return true;
}

bool QMemeryDataProperty::fromXml(XmlNode *xml)
{
    if(xml == NULL && xml->getTitle() != PROPERTY_TITLE)
    {
        return false;
    }
    setName(xml->getProperty("name"));

    MemeryValueItems items;

    foreach(XmlNode * node,xml->getChildren())
    {
        if(node->getTitle() == "Item")
        {
            tagMemeryValueInfo info;
            info.m_propertyName = node->getProperty("propertyName");
            info.m_dataUuid = node->getProperty("dataUuid");
            if(info.m_propertyName != "" && info.m_dataUuid != "")
            {
                items.append(info);
            }
        }
    }

    setValue(QVariant::fromValue<MemeryValueItems>(items));
    return true;
}
