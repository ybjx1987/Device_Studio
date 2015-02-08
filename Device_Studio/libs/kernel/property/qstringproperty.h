#ifndef QSTRINGPROPERTY_H
#define QSTRINGPROPERTY_H

#include "qabstractproperty.h"

class XmlNode;

class QStringProperty: public QAbstractProperty
{
    Q_OBJECT
public:
    QStringProperty(QAbstractProperty * parent = NULL);

    QString getValueText();
    QIcon   getValueIcon();

    void    setUuid(const QString & uuid);
protected:
    void    makeValue(XmlNode *xml);
    void    writeValue(XmlNode *xml);

protected:
    QString     m_uuid;
};

#endif // QSTRINGPROPERTY_H
