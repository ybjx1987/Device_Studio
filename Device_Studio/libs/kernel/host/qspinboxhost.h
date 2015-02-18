#ifndef QSPINBOXHOST_H
#define QSPINBOXHOST_H

#include "qabstractspinboxhost.h"

class KERNEL_EXPORT QSpinBoxHost : public QAbstractSpinBoxHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QSpinBoxHost(QAbstractWidgetHost* parent = NULL);

    static QAbstractHostInfo *getHostInfo();
protected slots:
    void    setValue(int value);
    int     getValue();

    void    setSingleStep(int singleStep);
    int     getSingleStep();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QSPINBOXHOST_H
