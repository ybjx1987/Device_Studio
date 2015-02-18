#ifndef QCOMBOBOXHOST_H
#define QCOMBOBOXHOST_H

#include "qwidgethost.h"

class KERNEL_EXPORT QComboBoxHost : public QWidgetHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QComboBoxHost(QAbstractWidgetHost * parent = NULL);

    static QWidgetHostInfo* getHostInfo();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QCOMBOBOXHOST_H
