#include "qabstracthost.h"

#include "../xmlnode.h"

#include <QVariant>

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

    xml->setTitle(property("host_title").toString());
}
