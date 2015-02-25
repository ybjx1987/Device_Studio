#ifndef QFLOATDATAHOST_H
#define QFLOATDATAHOST_H

#include "qabstractdatahost.h"

class KERNEL_EXPORT QFloatDataHost : public QAbstractDataHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QFloatDataHost(QAbstractHost * parent = NULL);

    static QAbstractHostInfo * getHostInfo();
protected:
    void initProperty();
    void initDefaultValue();
};

#endif // QFLOATDATAHOST_H
