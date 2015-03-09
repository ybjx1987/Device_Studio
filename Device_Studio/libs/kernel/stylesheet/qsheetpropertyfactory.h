#ifndef QSHEETPROPERTYFACTORY_H
#define QSHEETPROPERTYFACTORY_H

#include <QString>
#include <QMap>
#include <QMetaObject>

class QAbstractSheetType;

class TypeInfo
{
public:
    QString     m_property;
    QMetaObject m_metaObject;
    QString     m_name;
};

class QSheetPropertyFactory
{
public:
    static void registerProperty(const TypeInfo & info);
    static QAbstractSheetType* createProperty(const QString& name);
    static QStringList getPropertyInfo();

    static void registerInnerProperty();
protected:
    static QMap<QString,TypeInfo>     m_metaMap;
};

#endif // QSHEETPROPERTYFACTORY_H
