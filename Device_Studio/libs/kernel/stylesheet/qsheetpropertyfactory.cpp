#include "qsheetpropertyfactory.h"

#include "type/qabstractsheettype.h"
#include "type/qurlsheettype.h"

QMap<QString,QMetaObject>     QSheetPropertyFactory::m_metaMap;

void QSheetPropertyFactory::registerProperty(const QString & name,
                                             QMetaObject meta)
{
    if(m_metaMap.contains(name))
    {
        return;
    }

    m_metaMap.insert(name,meta);
}

QAbstractSheetType* QSheetPropertyFactory::createProperty(const QString &name)
{
    if(!m_metaMap.keys().contains(name))
    {
        return NULL;
    }
    QMetaObject meta = m_metaMap.value(name);
    QAbstractSheetType *pro = (QAbstractSheetType*)meta.newInstance();
    return pro;
}

QStringList QSheetPropertyFactory::getPropertyInfo()
{
    return m_metaMap.keys();
}

void QSheetPropertyFactory::registerInnerProperty()
{
    registerProperty("background-image",QUrlSheetType::staticMetaObject);
}
