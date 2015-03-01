#include "qstylesheetmanager.h"


#include "qstylesheetgroup.h"

#include "../xmlnode.h"

#include <QFile>
#include <QVariant>
#include <QDir>

QStyleSheetManager::QStyleSheetManager(QObject *parent) : QObject(parent)
{

}

QStyleSheetManager::~QStyleSheetManager()
{
    clear();
}

void QStyleSheetManager::save(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())
    {
        dir.mkpath(path);
    }
    QFile f(path+"/stylesheet.xml");

    if(!f.exists())
    {
        return;
    }

    if(!f.open(QFile::ReadOnly))
    {
        return;
    }

    QString buffer = f.readAll();
    f.close();

    XmlNode xml;

    if(!xml.load(buffer))
    {
        return;
    }

    if(xml.getTitle() != "StyleSheetGroups")
    {
        return;
    }

    foreach(XmlNode * obj,xml.getChildren())
    {
        if(obj->getTitle() == "Group")
        {
            QString name = path+"/"+obj->getText();
            QStyleSheetGroup * group = new QStyleSheetGroup;
            if(group->load(name))
            {
                m_groups.append(group);
                m_uuidToGroup.insert(group->getUuid(),group);
            }
            else
            {
                delete group;
            }
        }
    }
}

void QStyleSheetManager::load(const QString & path)
{
    clear();

    XmlNode xml;
    xml.setTitle("StyleSheetGroups");

    foreach(QStyleSheetGroup * g,m_groups)
    {
        if(g->save(g->property("fileName").toString()))
        {
            XmlNode * node = new XmlNode(&xml);
            node->setTitle("Group");
            node->setText(g->property("fileName").toString());
        }
    }

    QFile f(path +"/stylesheet.xml");

    if(!f.open(QFile::ReadWrite))
    {
        return;
    }

    f.resize(0);

    QString buffer;
    if(!xml.load(buffer))
    {
        f.close();
        return;
    }

    f.write(buffer.toLocal8Bit());
    f.close();
}

void QStyleSheetManager::addGroup(const QString &name)
{
    QStyleSheetGroup * group = new QStyleSheetGroup;

    group->setName(name);

    m_groups.append(group);
    m_uuidToGroup.insert(group->getUuid(),group);
    emit groupAdded(group);
}

void QStyleSheetManager::delGroup(QStyleSheetGroup *group)
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

void QStyleSheetManager::clear()
{
    qDeleteAll(m_groups);
    m_groups.clear();
    m_uuidToGroup.clear();
}

QList<QStyleSheetGroup*> QStyleSheetManager::getGroups()
{
    return m_groups;
}

QStringList QStyleSheetManager::getGroupNames()
{
    QStringList list;
    foreach(QStyleSheetGroup * g,m_groups)
    {
        list.append(g->getName());
    }
    return list;
}
