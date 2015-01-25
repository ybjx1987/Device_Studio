#include "qabstractproperty.h"

#include "../xmlnode.h"

QAbstractProperty::QAbstractProperty()
{

}

QAbstractProperty::~QAbstractProperty()
{

}

bool QAbstractProperty::equal(const QVariant &value)
{
    return m_value == value;
}

bool QAbstractProperty::isModified()
{
    return !equal(m_defaultValue);
}

bool QAbstractProperty::toXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }
    xml->clear();
    xml->setTitle(PROPERTY_TITLE);

}
