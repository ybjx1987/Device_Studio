#ifndef QFRAMEHOST_H
#define QFRAMEHOST_H

#include "qwidgethost.h"

class QFrameHost: public QWidgetHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QFrameHost(QAbstractWidgetHost *parent = 0);


    static QWidgetHostInfo * getHostInfo();
public slots:
    void    setFrameShape(int frameShape);
    int     getFrameShape();

    void    setFrameShadow(int frameShadow);
    int     getFrameShadow();
protected:
    void    initProperty();
    void    createObject();
};

#endif // QFRAMEHOST_H
