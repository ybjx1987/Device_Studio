#ifndef QSHEETPROPERTYFACTORY_H
#define QSHEETPROPERTYFACTORY_H

#include <QString>
#include <QMap>
#include <QMetaObject>

class QAbstractSheetType;

class QSheetPropertyFactory
{
public:
    static void registerProperty(const QString & name,QMetaObject mate);
    static QAbstractSheetType* createProperty(const QString& name);
    static QStringList getPropertyInfo();

    static void registerInnerProperty();
protected:
    static QMap<QString,QMetaObject>     m_metaMap;
};

#endif // QSHEETPROPERTYFACTORY_H
