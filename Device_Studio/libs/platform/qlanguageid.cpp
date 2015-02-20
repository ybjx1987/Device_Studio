#include "qlanguageid.h"

#include "../kernel/xmlnode.h"
#include <QFile>

QList<QLanguageInfo> QLanguageID::m_languageInfos;

void QLanguageID::load()
{
    m_languageInfos.clear();
    QFile file(":/inner/images/languages/translation.xml");

    if(!file.exists())
    {
        return;
    }

    if(!file.open(QFile::ReadOnly))
    {
        return;
    }

    QString str = file.readAll();

    XmlNode xml;
    if(!xml.load(str))
    {
        return;
    }

    if(xml.getTitle() != "Languages")
    {
        return;
    }

    QString name;

    foreach(XmlNode *obj,xml.getChildren())
    {
        QLanguageInfo info;
        info.m_icon = ":/inner/images/languages/"+obj->getProperty("icon");
        info.m_id = obj->getProperty("id");
        info.m_name = obj->getProperty("name");
        m_languageInfos.append(info);
    }
}

QList<QLanguageInfo> QLanguageID::getLanguageInfos()
{
    return m_languageInfos;
}

QLanguageInfo QLanguageID::getLanguageInfo(const QString &id)
{
    foreach(QLanguageInfo info,m_languageInfos)
    {
        if(info.m_id == id)
        {
            return info;
        }
    }
    return QLanguageInfo();
}
