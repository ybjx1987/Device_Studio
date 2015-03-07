#ifndef QSTYLESHEETITEM_H
#define QSTYLESHEETITEM_H

#include <QMap>
#include <QObject>

class XmlNode;
class QStyleSheetItemTitle;
class QAbstractSheetType;

class QStyleSheetItem : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheetItem(QObject *parent = 0);
    ~QStyleSheetItem();

    QList<QStyleSheetItemTitle*>    getTitles();
    QList<QAbstractSheetType*>  getPropertys();

    void    clear();

    bool    toXml(XmlNode * xml);
    bool    fromXml(XmlNode * xml);

    void    addTitle(QStyleSheetItemTitle * title);
    void    delTitle(QStyleSheetItemTitle * title);

    void    addProperty(QAbstractSheetType * property);
    void    delProperty(QAbstractSheetType * property);

    QString getUuid();
signals:
    void    titleAdded(QStyleSheetItemTitle * title);
    void    titleDeled(QStyleSheetItemTitle * title);

    void    propertyAdded(QAbstractSheetType * property);
    void    propertyDeled(QAbstractSheetType * property);
public slots:
protected:
    QList<QStyleSheetItemTitle*>    m_titles;
    QList<QAbstractSheetType*>  m_propertys;
    QString                         m_uuid;
};

#endif // QSTYLESHEETITEM_H
