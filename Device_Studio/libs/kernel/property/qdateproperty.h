#ifndef QDATEPROPERTY_H
#define QDATEPROPERTY_H

#include "qabstractproperty.h"

class XmlNode;

class KERNEL_EXPORT QDateProperty : public QAbstractProperty
{
public:
    QDateProperty(QAbstractProperty* parent = NULL);

    QString     getValueText();
    QIcon       getValueIcon();
protected:
    void        makeValue(XmlNode *xml);
    void        writeValue(XmlNode *xml);
};

#endif // QDATEPROPERTY_H
