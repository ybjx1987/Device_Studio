#ifndef QDOUBLESPINBOXHOST_H
#define QDOUBLESPINBOXHOST_H

#include "qabstractspinboxhost.h"

class KERNEL_EXPORT QDoubleSpinBoxHost : public QAbstractSpinBoxHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QDoubleSpinBoxHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo *getHostInfo();

protected:
    void    createObject();
    void    initProperty();
public slots:
    void    setValue(float value);
    float   getValue();

    void    setSingleStep(float singleStep);
    float   getSingleStep();

    void    setDecimals(int decimals);
    int     getDecimals();
};

#endif // QDOUBLESPINBOXHOST_H
