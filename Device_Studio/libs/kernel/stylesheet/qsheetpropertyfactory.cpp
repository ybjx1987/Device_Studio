#include "qsheetpropertyfactory.h"

#include "qabstractsheetproperty.h"

QMap<QString,QSheetPropertyInfo*>     QSheetPropertyFactory::m_metaMap;
QList<QSheetPropertyInfo*>            QSheetPropertyFactory::m_metas;

void QSheetPropertyFactory::registerProperty(QSheetPropertyInfo *info)
{
    if(m_metaMap.contains(info->m_name) || info == NULL)
    {
        return;
    }

    m_metaMap.insert(info->m_name,info);
    m_metas.append(info);
}

QAbstractSheetProperty* QSheetPropertyFactory::createProperty(const QString &name)
{
    QSheetPropertyInfo * info = m_metaMap.value(name);
    if(info == NULL)
    {
        return NULL;
    }

    QAbstractSheetProperty *pro = (QAbstractSheetProperty*)info->m_metaObject->newInstance();
    if(pro!=NULL)
    {
        pro->setProperty("proName",info->m_name);
    }
    return pro;
}

QList<QSheetPropertyInfo*> QSheetPropertyFactory::getPropertyInfo()
{
    return m_metas;
}

QSheetPropertyInfo * QSheetPropertyFactory::getPropertyInfo(const QString &name)
{
    return m_metaMap.value(name);
}

void QSheetPropertyFactory::registerInnerProperty()
{
}
