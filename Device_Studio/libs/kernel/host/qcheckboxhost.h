#ifndef QCHECKBOXHOST_H
#define QCHECKBOXHOST_H

#include "qabstractbuttonhost.h"

class QCheckBoxHost : public QAbstractButtonHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QCheckBoxHost(QAbstractWidgetHost *parent = 0);

    static QWidgetHostInfo * getHostInfo();
public slots:
    void    setTristate(bool tristate);
    bool    getTristate();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QCHECKBOXHOST_H
