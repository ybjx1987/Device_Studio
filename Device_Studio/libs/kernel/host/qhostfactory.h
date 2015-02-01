#ifndef QHOSTFACTORY_H
#define QHOSTFACTORY_H

#include <QString>
#include <QMap>
#include <QMetaObject>

class QAbstractHost;
class QAbstractHostInfo;

class QHostFactory
{
public:
    static void registerHost(QAbstractHostInfo *info);
    static QAbstractHost* createHost(const QString& name);
    static QList<QAbstractHostInfo*> getHostInfo();
    static QAbstractHostInfo *  getHostInfo(const QString &name);

    static void registerInnerHost();
protected:
    static QMap<QString,QAbstractHostInfo*>     m_metaMap;
    static QList<QAbstractHostInfo*>            m_metas;
};

#endif // QHOSTFACTORY_H
