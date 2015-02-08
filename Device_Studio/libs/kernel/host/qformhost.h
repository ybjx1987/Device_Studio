#ifndef QFORMHOST_H
#define QFORMHOST_H

#include "qabstractwidgethost.h"

class QFormHost : public QAbstractWidgetHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QFormHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo * getHostInfo();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QFORMHOST_H
