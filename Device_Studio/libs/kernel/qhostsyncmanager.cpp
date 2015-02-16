
#include "qhostsyncmanager.h"

#include "host/qabstracthost.h"

QHostSyncManager* QHostSyncManager::m_syncManager = NULL;

QHostSyncManager::QHostSyncManager(QObject *parent) :
    QObject(parent),
    m_timer(new QTimer(this))
{
    connect(m_timer,SIGNAL(timeout()),this,SLOT(hostSync()));
    m_timer->start(100);
}

QHostSyncManager::~QHostSyncManager()
{

}

void QHostSyncManager::hostSync()
{
    foreach(QAbstractHost * host,m_hosts)
    {
        host->updateProperty();
    }
}

void QHostSyncManager::insertHost(QAbstractHost * host)
{
    m_hosts.append(host);
    connect(host,SIGNAL(destroyed()),this,SLOT(hostReleased()));
}

void QHostSyncManager::hostReleased()
{
    m_hosts.removeAll((QAbstractHost*)sender());
}

QHostSyncManager* QHostSyncManager::getInstance()
{
    if(m_syncManager == NULL)
    {
        m_syncManager = new QHostSyncManager();
    }
    return m_syncManager;
}
