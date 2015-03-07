#include "qabstractsheettype.h"

#include "../../xmlnode.h"

#include <QIcon>

QAbstractSheetType::QAbstractSheetType(QAbstractSheetType *parent) :
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

}

void QAbstractSheetType::setName(const QString &name)
{
    m_name = name;
}

QString QAbstractSheetType::getName()
{
    return m_name;
}

void QAbstractSheetType::setShowName(const QString &showName)
{
    m_showName = showName;
}

QString QAbstractSheetType::getShowName()
{
    return m_showName;
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
    QString ret;
    ret = m_name+":"+getValue().toString()+";";
    return ret;
}

bool QAbstractSheetType::equal(const QVariant &value)
{
    return m_value == value;
}

bool QAbstractSheetType::toXml(XmlNode *xml)
{
    xml->setTitle("Property");
    xml->setProperty("type",property("proName").toString());
    xml->setProperty("value",m_value.toString());
    xml->setProperty("enabled",m_enabled?"true":"false");
    return true;
}

bool QAbstractSheetType::fromXml(XmlNode *xml)
{
    m_enabled = xml->getProperty("enabled") =="true";
    m_value = xml->getProperty("value");
    return true;
}

QList<QAbstractSheetType*> QAbstractSheetType::getChildren()
{
    return m_children;
}

QAbstractSheetType* QAbstractSheetType::getParent()
{
    return m_parent;
}
