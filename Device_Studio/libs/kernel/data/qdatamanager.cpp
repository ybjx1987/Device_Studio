#include "qdatamanager.h"

#include "qdatagroup.h"

QDataManager::QDataManager(QObject *parent) :
    QObject(parent)
{

}

QDataManager::~QDataManager()
{
    qDeleteAll(m_groups);
    m_groups.clear();
    m_nameToGroup.clear();
}

void QDataManager::addGroup(const QString &groupName, int index)
{
    if(groupName == "")
    {
        return;
    }
    if(m_nameToGroup.keys().contains(groupName))
    {
        return;
    }

    QDataGroup *group = new QDataGroup;

    group->setGroupName(groupName);

    if(index < 0 || index > m_groups.size())
    {
        index = m_groups.size();
    }

    m_groups.insert(index,group);
    m_nameToGroup.insert(groupName,group);

    emit groupAdded(group,index);
}

void QDataManager::delGroup(QDataGroup *group)
{
    if(!m_groups.contains(group))
    {
        return;
    }

    emit groupDeled(group);

    m_groups.removeAll(group);
    m_nameToGroup.remove(group->getGroupName());

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

    QDataGroup * group = m_nameToGroup.value(g);
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
