#ifndef QRESOURCEMANAGER_H
#define QRESOURCEMANAGER_H

#include <QObject>
#include <QMap>

class QResourceFile;
class XmlNode;

class QResourceManager : public QObject
{
    Q_OBJECT
public:
    explicit QResourceManager(QObject *parent = 0);
    ~QResourceManager();

    void    addResource(QResourceFile *resource);
    void    delResource(QResourceFile *resource);

    QList<QResourceFile*>   getResources();
    QResourceFile*          getResource(const QString &uuid);
    int                     getResourceQuote(const QString & uuid);

    void    useResource(const QString & uuid);
    void    unuseResource(const QString & uuid);

    void    clear();

    void    save(const QString & path);
    void    load(const QString & path);
signals:
    void resourceAdded(QResourceFile *resource);
    void resourceDeled(QResourceFile *resource);
public slots:
protected:
    void    registerResource(QResourceFile * resource);
    void    unregisterResource(QResourceFile * resource);
protected:
    QList<QResourceFile*>   m_resources;
    QMap<QResourceFile*,int>    m_resourceQuote;
    QMap<QString,QResourceFile*>    m_uuidToResource;
};

#endif // QRESOURCEMANAGER_H
