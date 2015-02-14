#ifndef QABSTRACTHOST_H
#define QABSTRACTHOST_H

#include "../kernellibglobal.h"

#include <QObject>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QMetaObject>

class QAbstractProperty;
class XmlNode;

class KERNEL_EXPORT QAbstractHostInfo
{
public:
    QString         m_type;
    QString         m_name;
    const QMetaObject     *m_metaObject;
};

class KERNEL_EXPORT QAbstractHost : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractHost(QAbstractHost *parent = 0);
    ~QAbstractHost();

    void                    clear();

    void                    setName(const QString &name);
    QString                 getName();

    void                    setUuid(const QString &uuid);
    QString                 getUuid();

    QObject*                getObject();

    static QAbstractHostInfo*      getHostInfo();

    void                    init();

    QList<QAbstractProperty*>   getPropertys();
    QAbstractProperty*      getProperty(const QString &name);

    QList<QAbstractHost*>   getChildrenHost();

    QVariant                getPropertyValue(const QString &name);
    void                    setPropertyValue(const QString &name,const QVariant &value);

    void                    insertHost(QAbstractHost * host,int index);
    void                    removeHost(QAbstractHost * host);

    void                    updateProperty();
protected:
    virtual void    createObject();
    virtual void    initProperty();
public:
    bool                    toXml(XmlNode * xml);
    bool                    fromXml(XmlNode * xml);
protected:
    void                    insertProperty(QAbstractProperty * property,int index = -1);
    void                    removeProperty(const QString &name);

protected:
    virtual     void        writeAttribute(XmlNode * xml);
    virtual     void        readAttribute(XmlNode * xml);
protected:
    QAbstractHost               *m_parent;
    QList<QAbstractHost*>       m_children;
    QList<QAbstractProperty*>   m_propertys;
    QMap<QString,QAbstractProperty*>    m_nameToProperty;
    QObject*                    m_object;

    QString                     m_name;
    QString                     m_uuid;
};

#endif // QABSTRACTHOST_H
