#ifndef QDATA_H
#define QDATA_H

#include "host/qabstracthost.h"

class QDataInfo : public QAbstractHostInfo
{
public:
    QDataInfo();
};

class QData : public QAbstractHost
{
    Q_OBJECT
public:
    QData();
    ~QData();
};

#endif // QDATA_H
