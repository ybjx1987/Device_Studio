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
    explicit QStyleSheetItem(const QString & type = "",QObject *parent = 0);
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
    void    replaceProperty(QAbstractSheetType * oldPro,
                            QAbstractSheetType * newPro);

    QString getUuid();

    QString getStyleSheet(const QString & title);

    void    setType(const QString & type);
signals:
    void    titleAdded(QStyleSheetItemTitle * title);
    void    titleDeled(QStyleSheetItemTitle * title);

    void    propertyAdded(QAbstractSheetType * property);
    void    propertyDeled(QAbstractSheetType * property);
    void    propertyReplaced(QAbstractSheetType * oldPro,
                             QAbstractSheetType * newPro);

    void    needUpdateStyleSheet();
public slots:
protected:
    QList<QStyleSheetItemTitle*>    m_titles;
    QList<QAbstractSheetType*>  m_propertys;
    QString                         m_uuid;
    QString                         m_type;
};

#endif // QSTYLESHEETITEM_H
