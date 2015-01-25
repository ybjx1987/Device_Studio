#ifndef QABSTRACTPROPERTY_H
#define QABSTRACTPROPERTY_H

#include "kernellibglobal.h"

#include <QObject>
#include <QMap>
#include <QVariant>

#define PROPERTY_TITLE  "Property"

class XmlNode;

class KERNEL_EXPORT QAbstractProperty : public QObject
{
    Q_OBJECT
public:
    QAbstractProperty();
    ~QAbstractProperty();

    bool        isModified();

    bool        equal(const QVariant &value);

    bool        toXml(XmlNode * xml);
protected:
    QMap<QString,QVariant>      m_attributes;
    QMap<QString,QVariant>      m_propertys;
    QVariant                    m_value;
    QVariant                    m_defaultValue;

};

#endif // QABSTRACTPROPERTY_H
