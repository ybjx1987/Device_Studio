#include "qabstractproperty.h"

#include "../xmlnode.h"

QAbstractProperty::QAbstractProperty(QAbstractProperty* parent):
    QObject(parent),
    m_parent(parent),
    m_visible(true),
    m_needExpanded(false),
    m_resetable(true),
    m_editable(true),
    m_canSame(true)
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
    if(xml == NULL && xml->getTitle() != PROPERTY_TITLE)
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

QList<QAbstractProperty*> QAbstractProperty::getChildren()
{
    return m_children;
}

void QAbstractProperty::makeValue(XmlNode *xml)
{
    setName(xml->getProperty("name"));
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
    xml->setProperty("value",m_value.toString());
}

QAbstractProperty& QAbstractProperty::operator =(const QAbstractProperty& pro)
{
    if(strcmp(metaObject()->className(),pro.metaObject()->className()) != 0)
    {
        return *this;
    }
    m_value = pro.m_value;
    m_name = pro.m_name;

    return *this;
}

void QAbstractProperty::setVisible(bool visible)
{
    m_visible = visible;
}

bool QAbstractProperty::getVisible()
{
    return m_visible;
}

void QAbstractProperty::setGroup(const QString &group)
{
    m_group = group;
}

QString QAbstractProperty::getGroup()
{
    return m_group;
}

void QAbstractProperty::setShowName(const QString &showName)
{
    m_showName = showName;
}

QString QAbstractProperty::getShowName()
{
    return m_showName;
}

void QAbstractProperty::setNeedExpanded(bool needExpanded)
{
    m_needExpanded = needExpanded;
}

bool QAbstractProperty::getNeedExpanded()
{
    return m_needExpanded;
}

bool QAbstractProperty::getResetable()
{
    return m_resetable;
}

void QAbstractProperty::setResetable(bool resetable)
{
    m_resetable = resetable;
}

bool QAbstractProperty::getEditable()
{
    return m_editable;
}

void QAbstractProperty::setEditable(bool editable)
{
    m_editable = editable;
}

bool QAbstractProperty::getCanSame()
{
    return m_canSame;
}

void QAbstractProperty::setCanSame(bool canSame)
{
    m_canSame = canSame;
}

void QAbstractProperty::connectUpdateValue()
{
    foreach(QAbstractProperty * child,m_children)
    {
        connect(child,SIGNAL(valueChanged(QVariant,QVariant)),this,SLOT(updateValue()));
        child->connectUpdateValue();
    }
}

void QAbstractProperty::disconnectUpdateValue()
{
    foreach(QAbstractProperty * child,m_children)
    {
        disconnect(child,SIGNAL(valueChanged(QVariant,QVariant)),this,SLOT(updateValue()));
        child->disconnectUpdateValue();
    }
}

void QAbstractProperty::updateValue()
{

}

QAbstractProperty* QAbstractProperty::getParent()
{
    return m_parent;
}
