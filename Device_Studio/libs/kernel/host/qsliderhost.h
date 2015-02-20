#ifndef QSLIDERHOST_H
#define QSLIDERHOST_H

#include "qabstractsliderhost.h"

class KERNEL_EXPORT QSliderHost : public QAbstractSliderHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QSliderHost(QAbstractWidgetHost * parent= NULL);

    static QAbstractHostInfo * getHostInfo();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QSLIDERHOST_H
