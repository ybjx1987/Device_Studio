#include "qabstracthost.h"

#include "qhostfactory.h"

#include "../property/qabstractproperty.h"
#include "../property/qbytearrayproperty.h"
#include "../qhostsyncmanager.h"
#include "../xmlnode.h"
#include "../property/qstringproperty.h"

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
    QHostSyncManager::getInstance()->insertHost(this);
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

    xml->setTitle(property("hostType").toString());

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

    if(xml->getTitle() != property("hostType").toString())
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
                if(h->getUuid() == "")
                {
                    h->setUuid(QUuid::createUuid().toString());
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
    xml->setProperty("type",property("hostName").toString());
    xml->setProperty("uuid",getUuid());
}

void QAbstractHost::readAttribute(XmlNode *xml)
{
    setUuid(xml->getProperty("uuid"));
}

void QAbstractHost::setUuid(const QString &uuid)
{
    m_uuid = uuid;

    QList<QAbstractProperty*> list = m_propertys;

    while(list.size()>0)
    {
        QAbstractProperty * pro = list.takeFirst();
        pro->setHostUuid(uuid);
        list += pro->getChildren();
    }
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
        connect(this,SIGNAL(destroyed()),
                m_object,SLOT(deleteLater()));
        connect(m_object,SIGNAL(destroyed()),
                this,SLOT(objectDeleted()));
        initProperty();
        m_object->installEventFilter(this);
        foreach(QAbstractProperty *pro,m_propertys)
        {
            pro->setValue(m_object->property(pro->getName().toLocal8Bit()));
        }
        setDefaultValue();
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
    connect(property,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(propertyChanged()));
    if(property->metaObject()->className() == QString("QStringProperty"))
    {
        QStringProperty *pro = (QStringProperty*)property;
        connect(pro,SIGNAL(needUpdate()),this,SLOT(strPropertyNeedUpdate()));
    }
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

QAbstractHost* QAbstractHost::getParent()
{
    return m_parent;
}

void QAbstractHost::insertHost(QAbstractHost *host, int index)
{
    if(index >=0 && index <= m_children.size())
    {
        if(host->m_parent != NULL)
        {
            disconnect(host,SIGNAL(needUpdate(QAbstractProperty*)),
                    this,SIGNAL(needUpdate(QAbstractProperty*)));
        }
        host->m_parent= this;
        m_children.insert(index,host);
        if(m_object->isWidgetType())
        {
            QWidget * wid = (QWidget*)host->getObject();
            wid->setParent((QWidget*)m_object);
            wid->setVisible(true);
        }
        else
        {
            host->getObject()->setParent(m_object);
        }
        connect(host,SIGNAL(needUpdate(QStringProperty*)),
                this,SIGNAL(needUpdate(QStringProperty*)));
        emit hostAdded(host,index);
    }
}

void QAbstractHost::removeHost(QAbstractHost *host)
{
    host->setPropertyValue("visible",false);
    emit hostRemoved(host);
    m_children.removeAll(host);
    host->getObject()->setParent(NULL);
}

void QAbstractHost::updateProperty()
{
    if(m_object == NULL)
    {
        return;
    }
    foreach(QAbstractProperty *property,m_propertys)
    {
        int status = property->property("syncStatus").toInt();
        if(status == 2)
        {
            property->setValue(m_object->property(property->getName().toLocal8Bit()));
        }
        else
        {
            m_object->setProperty(property->getName().toLocal8Bit(),
                                  property->getValue());
        }
        property->setProperty("syncStatus",0);
    }
}

void QAbstractHost::updateStringProperty()
{
    QList<QAbstractProperty*> list = m_propertys;

    while(list.size()>0)
    {
        QAbstractProperty * pro = list.takeFirst();
        if(pro->metaObject()->className() == QString("QStringProperty"))
        {
            emit needUpdate((QStringProperty*)pro);
        }
        list += pro->getChildren();
    }

    foreach(QAbstractHost * host,m_children)
    {
        host->updateStringProperty();
    }
}

void QAbstractHost::propertyChanged()
{
    if(m_object == NULL)
    {
        return;
    }
    QAbstractProperty * pro = (QAbstractProperty*) sender();
    m_object->setProperty(pro->getName().toLocal8Bit(),
                          pro->getValue());
}

void QAbstractHost::strPropertyNeedUpdate()
{
    QStringProperty * pro = (QStringProperty*)sender();

    emit needUpdate(pro);
}

void QAbstractHost::objectDeleted()
{
    m_object = NULL;
}

void QAbstractHost::setDefaultValue()
{
    foreach(QAbstractProperty * pro,m_propertys)
    {
        pro->setDefaultValue(pro->getValue());
    }

    foreach(QAbstractHost * host,m_children)
    {
        host->setDefaultValue();
    }
}
