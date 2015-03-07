#ifndef QSTYLESHEETITEMTITLE_H
#define QSTYLESHEETITEMTITLE_H

#include <QObject>
#include <QStringList>

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

    void    setSubControl(const QString & subControl);
    QString getSubControl();

    void    setStates(const QStringList & states);
    QStringList getStates();

    bool    fromXml(XmlNode * xml);
    bool    toXml(XmlNode * xml);

    bool    operator ==(const QStyleSheetItemTitle & title);
    bool    operator !=(const QStyleSheetItemTitle & title);
public slots:
protected:
    QString     m_name;
    QString     m_type;
    QString     m_subControl;
    QStringList m_states;
};

#endif // QSTYLESHEETITEMTITLE_H
