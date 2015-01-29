#ifndef QBYTEARRAYPROPERTY_H
#define QBYTEARRAYPROPERTY_H

#include "qabstractproperty.h"

class KERNEL_EXPORT QByteArrayProperty: public QAbstractProperty
{
    Q_OBJECT
public:
    QByteArrayProperty(QAbstractProperty * parent=NULL);

    QString getValueText();

    QIcon   getValueIcon();
};

#endif // QBYTEARRAYPROPERTY_H
