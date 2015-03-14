#include "qabstractsheettype.h"

#include "../../xmlnode.h"

#include <QIcon>

QAbstractSheetType::QAbstractSheetType(QAbstractSheetType *parent):
    QObject(parent),
    m_enabled(true),
    m_parent(parent)
{
    if(m_parent != NULL)
    {
        m_parent->m_children.append(this);
    }
}

QAbstractSheetType::~QAbstractSheetType()
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

void QAbstractSheetType::setName(const QString &name)
{
    m_name = name;
}

QString QAbstractSheetType::getName()
{
    return m_name;
}

void QAbstractSheetType::setEnabled(bool enabled)
{
    if(m_enabled != enabled)
    {
        m_enabled = enabled;
        emit enabledChanged(enabled);
    }
}

bool QAbstractSheetType::getEnabled()
{
    return m_enabled;
}

void QAbstractSheetType::setValue(const QVariant &value)
{
    if(!equal(value))
    {
        m_value = value;
        emit valueChanged(value);
        emit needUpdate();
    }
}

QVariant QAbstractSheetType::getValue()
{
    return m_value;
}

QString QAbstractSheetType::getValueText()
{
    return m_value.toString();
}

QIcon QAbstractSheetType::getValueIcon()
{
    return QIcon();
}

QString QAbstractSheetType::getStyleSheet()
{
    QString ret=getStyleSheetValue();
    if(ret == "Invalid" || ret == "")
    {
        return "";
    }
    else
    {
        ret = m_name+":"+ret;
        return ret;
    }
}

QString QAbstractSheetType::getStyleSheetValue()
{
    return getValueText();
}

bool QAbstractSheetType::equal(const QVariant &value)
{
    return m_value == value;
}

void QAbstractSheetType::toXml(XmlNode *xml)
{
    xml->setTitle("Property");
    xml->setProperty("type",getName());
    xml->setProperty("enabled",m_enabled?"true":"false");
    foreach(QAbstractSheetType * child,m_children)
    {
        XmlNode * obj = new XmlNode(xml);
        child->toXml(obj);
    }

    return;
}

void QAbstractSheetType::fromXml(XmlNode *xml)
{
    m_enabled = xml->getProperty("enabled") =="true";
    foreach(QAbstractSheetType * child,m_children)
    {
        foreach(XmlNode * obj,xml->getChildren())
        {
            if(obj->getProperty("type")== child->getName())
            {
                child->fromXml(obj);
                break;
            }
        }
    }

    return;
}

QAbstractSheetType * QAbstractSheetType::getParent()
{
    return m_parent;
}

QList<QAbstractSheetType*> QAbstractSheetType::getChildren()
{
    return m_children;
}

void QAbstractSheetType::setTypeProperty(const QString &xml)
{
    XmlNode node;
    if(node.load(xml))
    {
        parserProperty(&node);
    }
}

void QAbstractSheetType::parserProperty(XmlNode *)
{

}

void QAbstractSheetType::updateValue()
{

}
