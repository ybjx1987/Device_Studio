#ifndef QFLOATPROPERTY_H
#define QFLOATPROPERTY_H

#include "qabstractproperty.h"

class KERNEL_EXPORT QFloatProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    Q_INVOKABLE QFloatProperty(QAbstractProperty * parent = NULL);

    QString     getValueText();
    QIcon       getValueIcon();
};

#endif // QFLOATPROPERTY_H
