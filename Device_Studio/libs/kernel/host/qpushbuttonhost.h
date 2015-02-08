#ifndef QPUSHBUTTONHOST_H
#define QPUSHBUTTONHOST_H

#include "qabstractbuttonhost.h"


class QPushButtonHost : public QAbstractButtonHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QPushButtonHost(QAbstractWidgetHost *parent = 0);

    static QWidgetHostInfo * getHostInfo();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QPUSHBUTTONHOST_H
