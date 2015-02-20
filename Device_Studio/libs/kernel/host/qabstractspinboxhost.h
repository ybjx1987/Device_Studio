#ifndef QABSTRACTSPINBOXHOST_H
#define QABSTRACTSPINBOXHOST_H

#include "qwidgethost.h"

class KERNEL_EXPORT QAbstractSpinBoxHost : public QWidgetHost
{
    Q_OBJECT
public:
    QAbstractSpinBoxHost(QAbstractWidgetHost * parent = NULL);
protected:
    void    initProperty();
public slots:
    void    setFrame(bool frame);
    bool    getFrame();

    void    setWrapping(bool wrapping);
    bool    getWrapping();

    void    setReadOnly(bool readonly);
    bool    getReadOnly();

    void    setButtonSymbols(int buttonSymbols);
    int     getButtonSymbols();

    void    setAlignment(int alignment);
    int     getAlignment();
};

#endif // QABSTRACTSPINBOXHOST_H
