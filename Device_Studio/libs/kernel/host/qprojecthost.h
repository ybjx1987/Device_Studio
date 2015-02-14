#ifndef QPROJECTHOST_H
#define QPROJECTHOST_H

#include "qabstracthost.h"

class QProjectHost : public QAbstractHost
{
    Q_OBJECT
public:
    QProjectHost();
    ~QProjectHost();

    bool        save(const QString & filename);

protected:
    void        createObject();
    void        initProperty();

};

#endif // QPROJECTHOST_H
