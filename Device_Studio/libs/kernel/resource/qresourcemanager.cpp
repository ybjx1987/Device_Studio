#include "qresourcemanager.h"

#include "qresourcefile.h"
#include "../xmlnode.h"

#include <QResource>
#include <QFile>
#include <QDir>

QResourceManager::QResourceManager(const QString & type,QObject *parent) :
    QObject(parent),
    m_type(type)
{

}

QResourceManager::~QResourceManager()
{

}

void QResourceManager::clear()
{
    m_resourceQuote.clear();
    m_uuidToResource.clear();
    qDeleteAll(m_resources);
    m_resources.clear();
}

void QResourceManager::addResource(QResourceFile *resource)
{
    if(m_resources.contains(resource) || resource == NULL || resource->getUuid() == "")
    {
        return;
    }

    m_resources.append(resource);
    m_uuidToResource.insert(resource->getUuid(),resource);
    m_resourceQuote.insert(resource,0);
    emit resourceAdded(resource);
    useResource(resource->getUuid());
}

void QResourceManager::delResource(QResourceFile *resource)
{
    if(m_resources.contains(resource))
    {
        m_uuidToResource.remove(resource->getUuid());
        m_resourceQuote.remove(resource);
        m_resources.removeAll(resource);
        unregisterResource(resource);
        emit resourceDeled(resource);
        unuseResource(resource->getUuid());
        delete resource;
    }
}

QList<QResourceFile*>   QResourceManager::getResources()
{
    return m_resources;
}

QResourceFile* QResourceManager::getResource(const QString &uuid)
{
    return m_uuidToResource.value(uuid);
}

int QResourceManager::getResourceQuote(const QString &uuid)
{
    QResourceFile * resource = m_uuidToResource.value(uuid);
    if(resource != NULL)
    {
        return m_resourceQuote.value(resource);
    }
    else
    {
        return 0;
    }
}

void QResourceManager::registerResource(QResourceFile *resource)
{
    QResource::registerResource(resource->getRccData(),":/project/"+m_type);
}

void QResourceManager::unregisterResource(QResourceFile *resource)
{
    QResource::registerResource(resource->getRccData(),":/project/"+m_type);
}

void QResourceManager::useResource(const QString &uuid)
{
    QResourceFile * resource = m_uuidToResource.value(uuid);
    if(resource != NULL)
    {
        int quote = m_resourceQuote.value(resource);
        quote ++;
        m_resourceQuote.insert(resource,quote);
        if(quote == 1)
        {
            registerResource(resource);
        }
    }
}

void QResourceManager::unuseResource(const QString &uuid)
{
    QResourceFile * resource = m_uuidToResource.value(uuid);
    if(resource != NULL)
    {
        int quote = m_resourceQuote.value(resource);
        quote --;
        if(quote <=0)
        {
            quote = 0;
            unregisterResource(resource);
        }
        m_resourceQuote.insert(resource,quote);
    }
}

void QResourceManager::save(const QString & path)
{
    QDir dir(path);

    if(!dir.exists())
    {
        dir.mkpath(path);
    }

    XmlNode xml;
    xml.setTitle("Resources");


    foreach(QResourceFile *file,m_resources)
    {
        QString p = file->getPath();
        int last = p.lastIndexOf("/");
        if(last >= 0)
        {
            dir.mkpath(path+"/"+p.left(last));
        }
        QFile f(path+"/"+p);
        if(f.open(QFile::ReadWrite))
        {
            f.resize(0);
            f.write(file->getData());
            XmlNode * obj = new XmlNode(&xml);
            file->toXml(obj);
        }
        else
        {
            qDebug(f.errorString().toLocal8Bit());
        }
    }

    QFile f(path+"/resource.xml");

    if(!f.open(QFile::ReadWrite))
    {
        return;
    }

    f.resize(0);
    QString buffer;
    xml.save(buffer);
    f.write(buffer.toLocal8Bit());
}

void QResourceManager::load(const QString &path)
{
    clear();
    QFile f(path+"/resource.xml");

    if(!f.open(QFile::ReadWrite))
    {
        return;
    }

    XmlNode xml;
    if(!xml.load(QString::fromLocal8Bit(f.readAll())))
    {
        return;
    }
    if(xml.getTitle() != "Resources")
    {
        return;
    }
    foreach(XmlNode * obj,xml.getChildren())
    {
        QResourceFile *resource = new QResourceFile(
                    obj->getProperty("path"),
                    path+"/"+obj->getProperty("path"));
        resource->fromXml(obj);
        addResource(resource);
    }
}
