#ifndef QDIALHOST_H
#define QDIALHOST_H

#include "qabstractsliderhost.h"

class KERNEL_EXPORT QDialHost : public QAbstractSliderHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QDialHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo * getHostInfo();

protected:
    void    createObject();
    void    initProperty();
};

#endif // QDIALHOST_H
