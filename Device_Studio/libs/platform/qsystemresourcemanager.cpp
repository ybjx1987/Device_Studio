#include "qsystemresourcemanager.h"

#include <QApplication>
#include <QDir>
#include <QFileInfoList>

QSystemResourceManager::QSystemResourceManager(QObject * parent):
    QObject(parent),
    m_fileSystemWatcher(new QFileSystemWatcher(this))
{
    QDir dir(qApp->applicationDirPath()+"/systemResources");
    if(!dir.exists())
    {
        dir.mkpath(qApp->applicationDirPath()+"/systemResources");
    }
    refreshPath();

    connect(m_fileSystemWatcher,SIGNAL(directoryChanged(QString)),
            this,SLOT(directoryChanged(QString)));
}

QSystemResourceManager::~QSystemResourceManager()
{
    delete m_fileSystemWatcher;
}

void QSystemResourceManager::directoryChanged(const QString &path)
{
    if(path == qApp->applicationDirPath())
    {
        QDir dir(path+"/systemResources");
        if(!dir.exists())
        {
            m_resources.clear();
        }
    }
    else
    {
        refreshPath();
    }
}

void QSystemResourceManager::refreshPath()
{
    QString root = qApp->applicationDirPath()+"/systemResources";

    QDir dir(root);
    if(m_fileSystemWatcher->directories().size()>0)
    {
        m_fileSystemWatcher->removePaths(m_fileSystemWatcher->directories());
    }
    m_fileSystemWatcher->addPath(root);
    m_fileSystemWatcher->addPath(qApp->applicationDirPath());
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    m_resources.clear();
    while(list.size()>0)
    {
        QFileInfo info = list.takeFirst();
        if(info.isFile())
        {
            m_resources.append(info.filePath().remove(0,root.length()+1));
        }
        else
        {
            QDir dir(info.filePath());
            list += dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
            m_fileSystemWatcher->addPath(info.filePath());
        }
    }

    emit needUpdate();
}

QStringList QSystemResourceManager::getSystemResource()
{
    return m_resources;
}
