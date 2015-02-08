#ifndef QRADIOBUTTONHOST_H
#define QRADIOBUTTONHOST_H

#include "qabstractbuttonhost.h"

class QRadioButtonHost : public QAbstractButtonHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QRadioButtonHost(QAbstractWidgetHost *parent = 0);

    static QWidgetHostInfo * getHostInfo();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QRADIOBUTTONHOST_H
