#include "qdatamanager.h"

#include "qdatagroup.h"
#include "../xmlnode.h"

#include <QFile>

QDataManager::QDataManager(QObject *parent) :
    QObject(parent)
{

}

QDataManager::~QDataManager()
{
    qDeleteAll(m_groups);
    m_groups.clear();
    m_uuidToGroup.clear();
}

void QDataManager::addGroup(const QString &groupName, int index)
{
    if(groupName == "")
    {
        return;
    }

    foreach(QDataGroup * group,m_groups)
    {
        if(group->getGroupName() == groupName)
        {
            return;
        }
    }

    QDataGroup *group = new QDataGroup;

    group->setGroupName(groupName);

    if(index < 0 || index > m_groups.size())
    {
        index = m_groups.size();
    }

    m_groups.insert(index,group);
    m_uuidToGroup.insert(group->getUuid(),group);

    emit groupAdded(group,index);
}

void QDataManager::delGroup(QDataGroup *group)
{
    if(!m_groups.contains(group))
    {
        return;
    }

    m_groups.removeAll(group);
    m_uuidToGroup.remove(group->getUuid());

    emit groupDeled(group);

    delete group;
}

QAbstractDataHost * QDataManager::getData(const QString &name)
{
    int index = name.indexOf(".");
    if(index < 1)
    {
        return NULL;
    }
    QString g = name.left(index);
    QString n = name.mid(index+1);

    QDataGroup * group = getGroup(n);

    if(group == NULL)
    {
        return NULL;
    }

    return group->getData(n);
}

QAbstractDataHost * QDataManager::getDataByUuid(const QString &uuid)
{
    foreach(QDataGroup * group,m_groups)
    {
        QAbstractDataHost * data = group->getDataByUuid(uuid);
        if(data != NULL)
        {
            return data;
        }
    }

    return NULL;
}

QList<QDataGroup*>  QDataManager::getGroups()
{
    return m_groups;
}

QDataGroup* QDataManager::getGroup(const QString &name)
{
    foreach(QDataGroup * group,m_groups)
    {
        if(group->getGroupName() == name)
        {
            return group;
        }
    }
    return NULL;
}

QDataGroup * QDataManager::getGropuByUuid(const QString &uuid)
{
    return m_uuidToGroup.value(uuid);
}

bool QDataManager::save(const QString &path)
{
    QFile f(path+"/datas.xml");

    XmlNode xml;

    xml.setTitle("Datas");

    foreach(QDataGroup * g,m_groups)
    {
        XmlNode * group = new XmlNode(&xml);

        g->save(group);
    }

    QString buffer;

    if(!xml.save(buffer))
    {
        return false;
    }

    if(!f.open(QFile::ReadWrite))
    {
        return false;
    }

    f.write(buffer.toLocal8Bit());
    f.close();
    return true;
}

bool QDataManager::load(const QString &path)
{

    qDeleteAll(m_groups);
    m_groups.clear();
    m_uuidToGroup.clear();

    QFile f(path+"/datas.xml");

    if(!f.open(QFile::ReadOnly))
    {
        return false;
    }

    QString buffer = f.readAll();
    f.close();

    XmlNode xml;

    if(!xml.load(buffer))
    {
        return false;
    }

    QList<XmlNode*> list = xml.getChildren();

    foreach(XmlNode * node,list)
    {
        if(node->getTitle() == "Group")
        {
            QDataGroup * group = new QDataGroup;
            if(group->load(node))
            {
                m_groups.append(group);
                m_uuidToGroup.insert(group->getUuid(),group);
            }
        }
    }
    return true;
}
