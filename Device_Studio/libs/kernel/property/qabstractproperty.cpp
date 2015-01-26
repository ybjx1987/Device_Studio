#include "qabstractproperty.h"

#include "../xmlnode.h"

QAbstractProperty::QAbstractProperty(QAbstractProperty* parent):
    QObject(parent),
    m_parent(parent)
{
    if(m_parent != NULL)
    {
        m_parent->m_children.append(this);
    }
}

QAbstractProperty::~QAbstractProperty()
{
    while(m_children.size()>0)
    {
        delete m_children.first();
    }
    if(m_parent != NULL)
    {
        m_parent->m_children.removeAll(this);
    }
}

void QAbstractProperty::setValue(const QVariant &value)
{
    QVariant old = m_value;
    if(!equal(value))
    {
        m_value = value;
        emit valueChanged(m_value,old);
    }
}

void QAbstractProperty::reset()
{
    setValue(m_defaultValue);
}

void QAbstractProperty::setDefaultValue(const QVariant &value)
{
    m_defaultValue = value;
}

QVariant QAbstractProperty::getValue()
{
    return m_value;
}

bool QAbstractProperty::equal(const QVariant &value)
{
    return m_value == value;
}

bool QAbstractProperty::isModified()
{
    return !equal(m_defaultValue);
}

void QAbstractProperty::setType(const QString &type)
{
    m_type = type;
}

QString QAbstractProperty::getType()
{
    return m_type;
}

void QAbstractProperty::setName(const QString &name)
{
    m_name = name;
}

QString QAbstractProperty::getName()
{
    return m_name;
}

bool QAbstractProperty::toXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }
    xml->clear();
    xml->setTitle(PROPERTY_TITLE);
    writeValue(xml);

    XmlNode * node;
    foreach(QAbstractProperty* child,m_children)
    {
        node = new XmlNode(xml);
        if(!child->toXml(node))
        {
            xml->clear();
            return false;
        }
    }

    return true;
}

bool QAbstractProperty::fromXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }

    QList<XmlNode*>     subNodes = xml->getChildren();
    foreach(XmlNode * node,subNodes)
    {
        QAbstractProperty * pro = getChild(node->getProperty("name"));
        if(pro != NULL)
        {
            if(!pro->fromXml(node))
            {
                xml->clear();
                return false;
            }
        }
        else
        {
            xml->clear();
            return false;
        }
    }
    makeValue(xml);
    return true;
}

QAbstractProperty* QAbstractProperty::getChild(const QString &name)
{
    foreach(QAbstractProperty * pro,m_children)
    {
        if(pro->getName() == name)
        {
            return pro;
        }
    }
    return NULL;
}

void QAbstractProperty::makeValue(XmlNode *xml)
{
    setName(xml->getProperty("name"));
    setType(xml->getProperty("type"));
    QVariant v = xml->getProperty("value");
    if(m_value.type()>0)
    {
        v.convert(m_value.type());
    }
    m_value = v;
}

void QAbstractProperty::writeValue(XmlNode *xml)
{
    xml->setProperty("name",getName());
    xml->setProperty("type",getType());
    xml->setProperty("value",m_value.toString());
}

QAbstractProperty& QAbstractProperty::operator =(const QAbstractProperty& pro)
{
    if(m_type != getType())
    {
        return *this;
    }
    m_value = pro.m_value;
    m_name = pro.m_name;

    return *this;
}
