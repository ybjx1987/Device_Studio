#ifndef QHOSTSYNCMANAGER_H
#define QHOSTSYNCMANAGER_H

#include <QObject>
#include <QTimer>

class QAbstractHost;

class QHostSyncManager : public QObject
{
    Q_OBJECT
protected:
    explicit QHostSyncManager(QObject *parent = 0);
public:
    ~QHostSyncManager();

    void    insertHost(QAbstractHost * host);

    static QHostSyncManager* getInstance();
signals:

public slots:
    void    hostSync();
    void    hostReleased();
protected:
    QTimer          *m_timer;

    QList<QAbstractHost*>       m_hosts;

    static QHostSyncManager *m_syncManager;
};

#endif // QHOSTSYNCMANAGER_H
