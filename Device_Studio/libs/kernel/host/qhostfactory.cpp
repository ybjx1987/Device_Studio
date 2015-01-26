#include "qhostfactory.h"

#include "qabstracthost.h"

QMap<QString,QAbstractHostInfo*>     QHostFactory::m_metaMap;
QList<QAbstractHostInfo*>            QHostFactory::m_metas;

void QHostFactory::registerHost(QAbstractHostInfo *info)
{
    if(m_metaMap.contains(info->m_type) || info == NULL)
    {
        return;
    }

    m_metaMap.insert(info->m_type,info);
    m_metas.append(info);
}

QAbstractHost* QHostFactory::createHost(const QString &name)
{
    QAbstractHostInfo * info = m_metaMap.value(name);
    if(info == NULL)
    {
        return NULL;
    }

    QAbstractHost *host = (QAbstractHost*)info->m_metaObject->newInstance();
    if(host!=NULL)
    {
        host->init();
    }
    return host;
}

QList<QAbstractHostInfo*> QHostFactory::getHostInfo()
{
    return m_metas;
}

QAbstractHostInfo * QHostFactory::getHostInfo(const QString &name)
{
    return m_metaMap.value(name);
}
