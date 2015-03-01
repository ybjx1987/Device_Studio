#ifndef QSTYLESHEETMANAGER_H
#define QSTYLESHEETMANAGER_H

#include <QObject>
#include <QMap>

class QStyleSheetGroup;

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
signals:
    void    groupAdded(QStyleSheetGroup * group);
    void    groupDeled(QStyleSheetGroup * group);
public slots:
protected:
    QList<QStyleSheetGroup*>    m_groups;
    QMap<QString,QStyleSheetGroup*> m_uuidToGroup;
};

#endif // QSTYLESHEETMANAGER_H
