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
    explicit QStyleSheetGroup(QObject *parent = 0);
    ~QStyleSheetGroup();

    QList<QStyleSheetItem*> getItems();
    QStyleSheetItem *       getItem(const QString & uuid);

    void    addItem(QStyleSheetItem * item);
    void    delItem(QStyleSheetItem * item);

    bool    toXml(XmlNode * xml);
    bool    fromXml(XmlNode * xml);

    void    setName(const QString & name);
    QString getName();

    QString getUuid();
signals:
    void    itemAdded(QStyleSheetItem * item);
    void    itemDeled(QStyleSheetItem * item);
public slots:
protected:
    QList<QStyleSheetItem*> m_items;
    QMap<QString,QStyleSheetItem*>  m_uuidToItem;
    QString                 m_uuid;
    QString                 m_name;
};

#endif // QSTYLESHEETGROUP_H
