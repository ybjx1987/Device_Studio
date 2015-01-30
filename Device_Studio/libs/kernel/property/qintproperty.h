#ifndef QINTPROPERTY_H
#define QINTPROPERTY_H

#include "qabstractproperty.h"

class KERNEL_EXPORT QIntProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    Q_INVOKABLE QIntProperty(QAbstractProperty * parent = NULL);

    QString         getValueText();
    QIcon           getValueIcon();
};

#endif // QINTPROPERTY_H
