#ifndef QSYSTEMRESOURCEMANAGER_H
#define QSYSTEMRESOURCEMANAGER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QStringList>

class QSystemResourceManager : public QObject
{
    Q_OBJECT
public:
    explicit QSystemResourceManager(QObject * parent = NULL);
    ~QSystemResourceManager();

    QStringList getSystemResource();
protected slots:
    void directoryChanged(const QString & path);

signals:
    void needUpdate();
protected:
    void refreshPath();
protected:
    QFileSystemWatcher  *m_fileSystemWatcher;

    QStringList m_resources;
};

#endif // QSYSTEMRESOURCEMANAGER_H
