#include "qhostfactory.h"

#include "host/qabstracthost.h"

#include "xmlnode.h"

//名称和描述内容的对应关系
QMap<QString,QAbstractHostInfo*> QHostFactory::m_metaMap;
//Host描述列表
QList<QAbstractHostInfo*>        QHostFactory::m_metas;

/**
 * @brief 注册Host
 * @param info--Host的描述内容
 */
void QHostFactory::registerHost(QAbstractHostInfo *info)
{
    if(info == NULL)
    {
        return;
    }
    m_metaMap.insert(info->m_name,info);
    m_metas.append(info);
}

/**
 * @brief 创建Host
 * @param name--Host的名称
 * @return 创建的Host指针，如果创建不成功就会返回NULL
 */
QAbstractHost* QHostFactory::createHost(const QString &name)
{
    QAbstractHostInfo *info=m_metaMap->value(name);
    if(info == NULL)
    {
        return NULL;
    }
    const QMetaObject* obj=info->m_metaObject;
    QAbstractHost *host;
    if(obj!=NULL)
    {
        host=(QAbstractHost*)obj->newInstance();
        host->init();
    }

    return host;
}

/**
 * @brief 获取Host描述符
 * @return Host描述符
 */
QList<QAbstractHostInfo*> QHostFactory::getHostInfo()
{
    return m_metas;
}

/**
 * @brief 根据名称获取Host描述符
 * @param name--Host名称
 * @return Host的描述符，如果没有找到相应的Host描述符就会返回一个NULL
 */
QAbstractHostInfo* QHostFactory::getHostInfo(const QString &name)
{
    return m_metaMap->value(name);
}
