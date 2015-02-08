#ifndef QMEMERYDATAPROPERTY_H
#define QMEMERYDATAPROPERTY_H

#include "qabstractproperty.h"

class QMemeryDataProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    QMemeryDataProperty(QAbstractProperty * parent = NULL);

    QString         getValueText();
    QIcon           getValueIcon();

    bool            equal(const QVariant &value);


    virtual bool        toXml(XmlNode * xml);
    virtual bool        fromXml(XmlNode* xml);
};

#endif // QMEMERYDATAPROPERTY_H
