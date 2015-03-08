#ifndef QABSTRACTSHEETTYPE_H
#define QABSTRACTSHEETTYPE_H

#include <QObject>
#include <QVariant>

class XmlNode;

class QAbstractSheetType : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractSheetType();
    ~QAbstractSheetType();

    void    setName(const QString & name);
    QString getName();

    virtual void    setValue(const QVariant & value);
    QVariant        getValue();
    virtual QString getValueText();
    virtual QIcon   getValueIcon();
    virtual QString getStyleSheet();

    virtual bool    toXml(XmlNode * xml);
    virtual bool    fromXml(XmlNode * xml);

    virtual bool    equal(const QVariant & value);

    void            setEnabled(bool enabled);
    bool            getEnabled();
signals:
    void    enabledChanged(bool enabled);
    void    valueChanged(const QVariant & value);
    void    needUpdate();
public slots:
protected:
    QString     m_name;
    bool        m_enabled;
    QVariant    m_value;
};

#endif // QABSTRACTSHEETTYPE_H
