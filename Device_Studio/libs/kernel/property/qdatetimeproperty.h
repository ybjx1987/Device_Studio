#ifndef QDATETIMEPROPERTY_H
#define QDATETIMEPROPERTY_H

#include "qabstractproperty.h"

class XmlNode;

class KERNEL_EXPORT QDateTimeProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    QDateTimeProperty(QAbstractProperty *parent = NULL);

    QString getValueText();
    QIcon   getValueIcon();
protected:
    void   makeValue(XmlNode *xml);
    void   writeValue(XmlNode *xml);
};

#endif // QDATETIMEPROPERTY_H
