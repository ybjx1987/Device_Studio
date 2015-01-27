#ifndef QABSTRACTHOST_H
#define QABSTRACTHOST_H

#include "kernellibglobal.h"

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

    QAbstractHostInfo*      getHostInfo();

    void                    init();
protected:
    virtual void    createObject();
    virtual void    initProperty();
public:
    bool                    toXml(XmlNode * xml);
    bool                    fromXml(XmlNode * xml);

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

    static QAbstractHostInfo    *m_info;
};

#endif // QABSTRACTHOST_H
