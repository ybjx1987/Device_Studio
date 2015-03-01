#ifndef QSHEETPROPERTYFACTORY_H
#define QSHEETPROPERTYFACTORY_H

#include <QString>
#include <QMap>
#include <QMetaObject>

class QSheetPropertyInfo;
class QAbstractSheetProperty;

class QSheetPropertyFactory
{
public:
    static void registerProperty(QSheetPropertyInfo *info);
    static QAbstractSheetProperty* createProperty(const QString& name);
    static QList<QSheetPropertyInfo*> getPropertyInfo();
    static QSheetPropertyInfo *  getPropertyInfo(const QString &name);

    static void registerInnerProperty();
protected:
    static QMap<QString,QSheetPropertyInfo*>     m_metaMap;
    static QList<QSheetPropertyInfo*>            m_metas;
};

#endif // QSHEETPROPERTYFACTORY_H
