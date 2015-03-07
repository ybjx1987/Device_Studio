#ifndef QABSTRACTSHEETTYPE_H
#define QABSTRACTSHEETTYPE_H

#include <QObject>
#include <QVariant>

class XmlNode;

class QAbstractSheetType : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractSheetType(QAbstractSheetType *parent = 0);
    ~QAbstractSheetType();

    void    setName(const QString & name);
    QString getName();

    void    setShowName(const QString & showName);
    QString getShowName();

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

    QAbstractSheetType *getParent();
    QList<QAbstractSheetType*>  getChildren();
signals:
    void    enabledChanged(bool enabled);
    void    valueChanged(const QVariant & value);
public slots:
protected:
    QString     m_name;
    QString     m_showName;
    bool        m_enabled;
    QVariant    m_value;

    QAbstractSheetType  *m_parent;
    QList<QAbstractSheetType*>  m_children;
};

#endif // QABSTRACTSHEETTYPE_H
