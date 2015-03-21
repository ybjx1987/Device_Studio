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
            QString getStyleSheet();
    virtual QString getStyleSheetValue();

    virtual void    toXml(XmlNode * xml);
    virtual void    fromXml(XmlNode * xml);

    virtual bool    equal(const QVariant & value);

    void            setEnabled(bool enabled);
    bool            getEnabled();

    void    setTypeProperty(const QString &xml);

    void    setType(const QString & type);
signals:
    void    enabledChanged(bool enabled);
    void    valueChanged(const QVariant & value);
    void    needUpdate();
protected:
    virtual void    parserProperty(XmlNode * xml);
protected:
    QString     m_name;
    bool        m_enabled;
    QVariant    m_value;
    QString     m_type;
};

#endif // QABSTRACTSHEETTYPE_H
