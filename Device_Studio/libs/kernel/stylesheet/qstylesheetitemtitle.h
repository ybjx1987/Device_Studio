#ifndef QSTYLESHEETITEMTITLE_H
#define QSTYLESHEETITEMTITLE_H

#include <QObject>

class XmlNode;

class QStyleSheetItemTitle : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheetItemTitle(QObject *parent = 0);
    ~QStyleSheetItemTitle();

    void    setName(const QString & name);
    QString getName();

    void    setType(const QString & type);
    QString getType();

    void    setEnabled(bool enabled);
    bool    getEnabled();

    bool    fromXml(XmlNode * xml);
    bool    toXml(XmlNode * xml);

signals:
    void    propertyChanged(const QString & proName);
public slots:
protected:
    QString     m_name;
    QString     m_type;
    bool        m_enabled;
};

#endif // QSTYLESHEETITEMTITLE_H
