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
    QString getUuid();

    void    setTranslation(bool translation);
    bool    getTranslation();
protected:
    void    makeValue(XmlNode *xml);
    void    writeValue(XmlNode *xml);
signals:
    void    needUpdate();
protected:
    QString     m_uuid;
    bool        m_translation;
};

#endif // QSTRINGPROPERTY_H
