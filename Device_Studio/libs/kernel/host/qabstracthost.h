#ifndef QABSTRACTHOST_H
#define QABSTRACTHOST_H

#include "kernellibglobal.h"

#include <QObject>
#include <QList>

class QAbstractProperty;

class KERNEL_EXPORT QAbstractHost : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractHost(QAbstractHost *parent = 0);
    ~QAbstractHost();

public:
    bool                    toXml(XmlNode * xml);
    bool                    fromXml(XmlNode * xml);
protected:
    QAbstractHost               *m_parent;
    QList<QAbstractHost*>       m_children;
    QList<QAbstractProperty*>   m_propertys;
    QMap<QString,QAbstractProperty*>    m_nameToProperty;
    QObject*                    m_object;
    QMap<QString,QString>       m_attributes;
    QTimer                      *m_timer;

};

#endif // QABSTRACTHOST_H
