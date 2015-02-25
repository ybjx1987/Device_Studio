#ifndef QABSTRACTDATAHOST_H
#define QABSTRACTDATAHOST_H

#include "../host/qabstracthost.h"

#include <QVariant>

class KERNEL_EXPORT QDataHostInfo : public QAbstractHostInfo
{
public:
    QDataHostInfo(){m_type="Data";}

    QString     m_showName;
};

class KERNEL_EXPORT QAbstractDataHost : public QAbstractHost
{
    Q_OBJECT
public:
    QAbstractDataHost(QAbstractHost * parent = NULL);

    virtual QVariant    getValue();
    virtual void        setValue(const QVariant & value);
    virtual bool        equal(const QVariant &value);
protected:
    void    createObject();
    void    initProperty();
protected:
    virtual void    initDefaultValue();
};

#endif // QABSTRACTDATAHOST_H
