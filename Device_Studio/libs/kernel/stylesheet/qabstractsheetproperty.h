#ifndef QABSTRACTSHEETPROPERTY_H
#define QABSTRACTSHEETPROPERTY_H

#include <QObject>
#include <QVariant>

class XmlNode;

class QSheetPropertyInfo
{
public:
    QString     m_name;
    QString     m_showName;
    QMetaObject *m_metaObject;
};

class QAbstractSheetProperty : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractSheetProperty(QObject *parent = 0);
    ~QAbstractSheetProperty();

    void    setName(const QString & name);
    QString getName();

    void    setShowName(const QString & showName);
    QString getShowName();

    virtual void    setValue(const QVariant & value);
    QVariant        getValue();
    virtual QString getValueText();
    virtual QString getStleSheet();

    virtual bool    toXml(XmlNode * xml);
    virtual bool    fromXml(XmlNode * xml);

    virtual bool    equal(const QVariant & value);

    void            setEnabled(bool enabled);
    bool            getEnabled();
signals:
    void    enabledChanged(bool enabled);
    void    valueChanged(const QVariant & value);
public slots:
protected:
    QString     m_name;
    QString     m_showName;
    bool        m_enabled;
    QVariant    m_value;
};

#endif // QABSTRACTSHEETPROPERTY_H
