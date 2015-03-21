#ifndef QSTYLESHEETGROUP_H
#define QSTYLESHEETGROUP_H

#include <QObject>
#include <QMap>

class QStyleSheetItem;
class XmlNode;

class QStyleSheetGroup : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheetGroup(const QString & type,QObject *parent = 0);
    ~QStyleSheetGroup();

    QList<QStyleSheetItem*> getItems();
    QStyleSheetItem *       getItem(const QString & uuid);

    void    addItem(QStyleSheetItem * item);
    void    delItem(QStyleSheetItem * item);

    void    setName(const QString & name);
    QString getName();

    QString getUuid();

    bool    load(const QString & filePath);
    bool    save(const QString & filePath);

    void    clear();
signals:
    void    itemAdded(QStyleSheetItem * item);
    void    itemDeled(QStyleSheetItem * item);
    void    needUpdateStyleSheet(const QList<QStyleSheetItem*> &items);
protected:
    bool    toXml(XmlNode * xml);
    bool    fromXml(XmlNode * xml);
protected slots:
    void    needUpdateStyleSheet();
protected:
    QList<QStyleSheetItem*> m_items;
    QMap<QString,QStyleSheetItem*>  m_uuidToItem;
    QString                 m_uuid;
    QString                 m_name;
    QString                 m_type;
};

#endif // QSTYLESHEETGROUP_H
