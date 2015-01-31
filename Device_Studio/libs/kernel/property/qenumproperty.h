#ifndef QENUMPROPERTY_H
#define QENUMPROPERTY_H

#include "qabstractproperty.h"

class KERNEL_EXPORT QEnumProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    Q_INVOKABLE QEnumProperty(QAbstractProperty *project = NULL);

    QString     getValueText();
    QIcon       getValueIcon();
};

#endif // QENUMPROPERTY_H
