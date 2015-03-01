#ifndef QSTYLESHEETITEM_H
#define QSTYLESHEETITEM_H

#include <QMap>
#include <QObject>

class XmlNode;
class QStyleSheetItemTitle;
class QAbstractSheetProperty;

class QStyleSheetItem : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheetItem(QObject *parent = 0);
    ~QStyleSheetItem();

    QList<QStyleSheetItemTitle*>    getTitles();
    QList<QAbstractSheetProperty*>  getPropertys();

    void    clear();

    bool    toXml(XmlNode * xml);
    bool    fromXml(XmlNode * xml);

    void    addTitle(QStyleSheetItemTitle * title);
    void    delTitle(QStyleSheetItemTitle * title);

    void    addProperty(QAbstractSheetProperty * property);
    void    delProperty(QAbstractSheetProperty * property);

    QString getUuid();
signals:
    void    titleAdded(QStyleSheetItemTitle * title);
    void    titleDeled(QStyleSheetItemTitle * title);

    void    propertyAdded(QAbstractSheetProperty * property);
    void    propertyDeled(QAbstractSheetProperty * property);
public slots:
protected:
    QList<QStyleSheetItemTitle*>    m_titles;
    QList<QAbstractSheetProperty*>  m_propertys;
    QString                         m_uuid;
};

#endif // QSTYLESHEETITEM_H
