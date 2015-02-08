#ifndef QBOOLPROPERTY_H
#define QBOOLPROPERTY_H

#include "qabstractproperty.h"

class KERNEL_EXPORT QBoolProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    QBoolProperty(QAbstractProperty * parent = NULL);

    QString     getValueText();
    QIcon       getValueIcon();
};

#endif // QBOOLPROPERTY_H
