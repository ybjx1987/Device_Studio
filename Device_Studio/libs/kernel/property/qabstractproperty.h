#ifndef QABSTRACTPROPERTY_H
#define QABSTRACTPROPERTY_H

#include "../kernellibglobal.h"

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

    void                setDefaultValue(const QVariant &value);
    bool                isModified();

    bool                equal(const QVariant &value);

    virtual bool        toXml(XmlNode * xml);
    virtual bool        fromXml(XmlNode* xml);

    QAbstractProperty*  getChild(const QString & name);
    QList<QAbstractProperty*>       getChildren();

    QAbstractProperty*  getParent();

    QString             getName();
    void                setName(const QString &name);

    bool                getVisible();
    void                setVisible(bool visible);

    QString             getGroup();
    void                setGroup(const QString &group);

    QString             getShowName();
    void                setShowName(const QString &showName);

    bool                getNeedExpanded();
    void                setNeedExpanded(bool needExpanded);

    bool                getResetable();
    void                setResetable(bool resetable);

    bool                getEditable();
    void                setEditable(bool editable);

    bool                getCanSame();
    void                setCanSame(bool canSame);

    QAbstractProperty&  operator =(const QAbstractProperty & pro);
public slots:
    void                reset();
protected slots:
    virtual void        updateValue();
protected:
    virtual void        makeValue(XmlNode * xml);
    virtual void        writeValue(XmlNode * xml);

    void                connectUpdateValue();
    void                disconnectUpdateValue();
signals:
    void                valueChanged(const QVariant &now,const QVariant &old);
protected:
    QAbstractProperty           *m_parent;
    QList<QAbstractProperty*>   m_children;

    QString                     m_type;
    QString                     m_name;

    QVariant                    m_value;
    QVariant                    m_defaultValue;

    bool                        m_visible;
    QString                     m_group;
    QString                     m_showName;
    bool                        m_needExpanded;
    bool                        m_resetable;
    bool                        m_editable;
    bool                        m_canSame;
};

#endif // QABSTRACTPROPERTY_H
