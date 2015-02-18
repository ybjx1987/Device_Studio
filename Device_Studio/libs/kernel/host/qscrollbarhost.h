#ifndef QSCROLLBARHOST_H
#define QSCROLLBARHOST_H

#include "qabstractsliderhost.h"

class QScrollBarHost : public QAbstractSliderHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QScrollBarHost(QAbstractWidgetHost* parent = NULL);

    static QAbstractHostInfo *getHostInfo();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QSCROLLBARHOST_H
