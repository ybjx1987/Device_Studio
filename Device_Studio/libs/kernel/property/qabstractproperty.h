#ifndef QABSTRACTPROPERTY_H
#define QABSTRACTPROPERTY_H

#include "kernellibglobal.h"

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QIcon>

#define PROPERTY_TITLE  "Property"

class XmlNode;

class KERNEL_EXPORT QAbstractProperty : public QObject
{
    Q_OBJECT
public:
    QAbstractProperty(QAbstractProperty *parent = 0);
    ~QAbstractProperty();

    virtual void        setValue(const QVariant &value);
    virtual QVariant    getValue();
    virtual QString     getValueText() = 0;
    virtual QIcon       getValueIcon() = 0;

    void                reset();

    void                setDefaultValue(const QVariant &value);
    bool                isModified();

    bool                equal(const QVariant &value);

    bool                toXml(XmlNode * xml);
    bool                fromXml(XmlNode* xml);

    QAbstractProperty*  getChild(const QString & name);

    QString             getType();
    void                setType(const QString &type);

    QString             getName();
    void                setName(const QString &name);

    QAbstractProperty&  operator =(const QAbstractProperty & pro);
protected:
    virtual void        makeValue(XmlNode * xml);
    virtual void        writeValue(XmlNode * xml);
signals:
    void                valueChanged(const QVariant &now,const QVariant &old);
protected:
    QAbstractProperty           *m_parent;
    QList<QAbstractProperty*>   m_children;

    QString                     m_type;
    QString                     m_name;

    QVariant                    m_value;
    QVariant                    m_defaultValue;

};

#endif // QABSTRACTPROPERTY_H
