#ifndef QSTYLESHEETMANAGER_H
#define QSTYLESHEETMANAGER_H

#include <QObject>
#include <QMap>

class QStyleSheetGroup;
class QStyleSheetItem;

class QStyleSheetManager : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheetManager(QObject *parent = 0);
    ~QStyleSheetManager();

    void    load(const QString & path);
    void    save(const QString & path);

    void    addGroup(const QString & name);
    void    delGroup(QStyleSheetGroup * group);

    void    clear();
    void    clearFile(const QString & path);

    QList<QStyleSheetGroup*> getGroups();
    QStringList              getGroupNames();
signals:
    void    groupAdded(QStyleSheetGroup * group);
    void    groupDeled(QStyleSheetGroup * group);

    void    needUpdateStyleSheet(const QList<QStyleSheetItem*> &items);
public slots:
protected:
    QList<QStyleSheetGroup*>    m_groups;
    QMap<QString,QStyleSheetGroup*> m_uuidToGroup;
};

#endif // QSTYLESHEETMANAGER_H
