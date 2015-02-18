#ifndef QTIMEPROPERTY_H
#define QTIMEPROPERTY_H

#include "qabstractproperty.h"

class XmlNode;

class KERNEL_EXPORT QTimeProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    QTimeProperty(QAbstractProperty * parent=NULL);

    QString     getValueText();
    QIcon       getValueIcon();
protected:
    void        makeValue(XmlNode *xml);
    void        writeValue(XmlNode *xml);
};

#endif // QTIMEPROPERTY_H
