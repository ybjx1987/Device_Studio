#include "qabstracthost.h"

#include "qhostfactory.h"

#include "../property/qabstractproperty.h"
#include "../property/qbytearrayproperty.h"

#include "../xmlnode.h"

#include <QVariant>
#include <QUuid>
#include <QWidget>

QAbstractHost::QAbstractHost(QAbstractHost *parent) :
    QObject(parent),
    m_parent(parent)
{
    if(m_parent != NULL)
    {
        m_parent->m_children.append(this);
    }
}

QAbstractHost::~QAbstractHost()
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


bool QAbstractHost::toXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }

    xml->setTitle(getHostInfo()->m_type);

    writeAttribute(xml);

    XmlNode *obj;
    foreach(QAbstractProperty* pro,m_propertys)
    {
        if(pro->isModified())
        {
            obj = new XmlNode(xml);
            if(!pro->toXml(obj))
            {
                xml->clear();
                return false;
            }
        }
    }

    foreach(QAbstractHost * h,m_children)
    {
        obj = new XmlNode(xml);
        if(!h->toXml(obj))
        {
            xml->clear();
            return false;
        }
    }
    return true;
}

bool QAbstractHost::fromXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }

    if(xml->getTitle() != getHostInfo()->m_type)
    {
        return false;
    }

    clear();

    readAttribute(xml);

    if(getUuid() == "")
    {
        setUuid(QUuid::createUuid().toString());
    }

    QList<XmlNode*> subNodes = xml->getChildren();

    foreach(XmlNode* obj,subNodes)
    {
        if(obj->getTitle() == PROPERTY_TITLE)
        {
            QAbstractProperty * pro = m_nameToProperty.value(obj->getProperty("name"));
            if(pro == NULL || !pro->fromXml(obj))
            {
                xml->clear();
                return false;
            }
        }
        else
        {
            QAbstractHost *h = QHostFactory::createHost(obj->getProperty("type"));
            if(h!=NULL)
            {
                if(!h->fromXml(obj))
                {
                    xml->clear();
                    return false;
                }
                h->m_parent = this;
                m_children.append(h);
                if(h->m_object->isWidgetType())
                {
                    QWidget* w = (QWidget*)h->m_object;
                    w->setParent((QWidget*)m_object);
                    w->setVisible(true);
                }
                else
                {
                    h->m_object->setParent(m_object);
                }
            }
        }
    }
    return true;
}

void QAbstractHost::clear()
{
    while(m_children.size()>0)
    {
        delete m_children.first();
    }
}

void QAbstractHost::writeAttribute(XmlNode *xml)
{
    xml->setProperty("name",getName());
    xml->setProperty("uuid",getUuid());
}

void QAbstractHost::readAttribute(XmlNode *xml)
{
    setName(xml->getProperty("name"));
    setUuid(xml->getProperty("uuid"));
}

void QAbstractHost::setName(const QString &name)
{
    m_name = name;
}

QString QAbstractHost::getName()
{
    return m_name;
}

void QAbstractHost::setUuid(const QString &uuid)
{
    m_uuid = uuid;
}

QString QAbstractHost::getUuid()
{
    return m_uuid;
}

QAbstractHostInfo* QAbstractHost::getHostInfo()
{
    QAbstractHostInfo * info = new QAbstractHostInfo();
    info->m_metaObject = &(QAbstractHost::staticMetaObject);
    info->m_type = "abstract";
    return info;
}

void QAbstractHost::init()
{
    createObject();
    if(m_object != NULL)
    {
        initProperty();
        m_object->installEventFilter(this);
        foreach(QAbstractProperty *pro,m_propertys)
        {
            pro->setValue(m_object->property(pro->getName().toLocal8Bit()));
        }
    }
}

void QAbstractHost::createObject()
{
    m_object = NULL;
}

void QAbstractHost::initProperty()
{
    QByteArrayProperty  *pro = new QByteArrayProperty();
    pro->setName("objectName");
    pro->setShowName(tr("Name"));
    pro->setGroup("Attributes");
    insertProperty(pro);
}

void QAbstractHost::insertProperty(QAbstractProperty *property, int index)
{
    if(index < 0 || index > m_propertys.size())
    {
        index = m_propertys.size();
    }

    if(m_propertys.contains(property))
    {
        m_propertys.removeAll(property);
    }

    m_propertys.insert(index,property);
    m_nameToProperty.insert(property->getName(),property);
}

void QAbstractHost::removeProperty(const QString &name)
{
    QAbstractProperty * pro = m_nameToProperty.value(name);
    if(pro != NULL)
    {
        m_nameToProperty.remove(name);
        m_propertys.removeAll(pro);
        delete pro;
    }
}

QList<QAbstractProperty*>   QAbstractHost::getPropertys()
{
    return m_propertys;
}

QAbstractProperty * QAbstractHost::getProperty(const QString &name)
{
    QStringList list = name.split(".");
    if(list.size()>0)
    {
        QAbstractProperty * pro = m_nameToProperty.value(list.takeFirst());
        if(pro != NULL)
        {
            while(list.size() > 0)
            {
                pro = pro->getChild(list.takeFirst());
                if(pro == NULL)
                {
                    break;
                }
            }
            return pro;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

QVariant QAbstractHost::getPropertyValue(const QString &name)
{
    QAbstractProperty * pro = getProperty(name);
    if(pro != NULL)
    {
        return pro->getValue();
    }
    else
    {
        return QVariant();
    }
}

void QAbstractHost::setPropertyValue(const QString &name, const QVariant &value)
{
    QAbstractProperty * pro = getProperty(name);
    if(pro != NULL)
    {
        pro->setValue(value);
    }
}

QObject * QAbstractHost::getObject()
{
    return m_object;
}

QList<QAbstractHost*> QAbstractHost::getChildrenHost()
{
    return m_children;
}
