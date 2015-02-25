#include "qdatagroup.h"

#include "qabstractdatahost.h"

#include <QUuid>

QDataGroup::QDataGroup(QObject *parent) : QObject(parent)
{
    m_uuid = QUuid::createUuid().toString();
}

QDataGroup::~QDataGroup()
{
    qDeleteAll(m_datas);
}

void QDataGroup::setGroupName(const QString &groupName)
{
    if(m_groupName != groupName)
    {
        m_groupName = groupName;
        emit groupNameChanged();
    }
}

QString QDataGroup::getGroupName()
{
    return m_groupName;
}

QString QDataGroup::getUuid()
{
    return m_uuid;
}

void QDataGroup::addData(QAbstractDataHost *data,int index)
{
    if(m_datas.contains(data))
    {
        return;
    }
    if(index < 0 || index > m_datas.size())
    {
        index = m_datas.size();
    }
    m_datas.insert(index,data);

    emit dataAdded(data,index);
}

void QDataGroup::delData(QAbstractDataHost *data)
{
    if(!m_datas.contains(data))
    {
        return;
    }

    m_datas.removeAll(data);

    emit dataDeled(data);

    delete data;
}

QAbstractDataHost * QDataGroup::getData(const QString &name)
{
    foreach(QAbstractDataHost * data,m_datas)
    {
        if(data->getPropertyValue("objectName").toString() == name)
        {
            return data;
        }
    }
    return NULL;
}

QList<QAbstractDataHost*> QDataGroup::getDatas()
{
    return m_datas;
}

QAbstractDataHost* QDataGroup::getDataByUuid(const QString &uuid)
{
    foreach(QAbstractDataHost * data,m_datas)
    {
        if(data->getUuid() == uuid)
        {
            return data;
        }
    }

    return NULL;
}
