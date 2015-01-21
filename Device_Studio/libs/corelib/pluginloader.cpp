#include "pluginloader.h"

#include "qabstractplugin.h"
#include "xmlnode.h"

#include <QApplication>
#include <QPluginLoader>
#include <QDir>

QMap<QString,QMap<QString,QAbstractPlugin*> > PluginLoader::m_plugins;


/**
 * @brief 加载插件，根据插件描述文件来进行插件，插件描述符会记录需要加载的插件所在文件夹的相对路径。
 * @param xmlFileName--插件描述文件的全路径。
 * @return 正确加载插件就返回true，否则返回false
 */
bool PluginLoader::loadPlugin(const QString &xmlFileName)
{
    releasePlugin();

    XmlNode xml;
    QFile f(xmlFileName);
    if(!f.open(QFile::ReadOnly))
    {
        return false;
    }
    QString str=f.readAll();
    if(!xml.load(str))
    {
        return false;
    }
    if(xml.getTitle()!="Plugin")
    {
        return false;
    }
    QList<XmlNode*> paths=xml.getChildren();
    QString path=QApplication::applicationDirPath();

    //遍历所有的文件夹
    foreach(XmlNode* obj,paths)
    {
        QString p=path+"/"+obj->getProperty("path");
        QDir dir(p);
        QFileInfoList list=dir.entryInfoList(QDir::Files);
        for(int i=0;i<list.size();i++)
        {
            QPluginLoader load(list.at(i).filePath());

            //加载插件
            if(load.load())
            {
                QAbstractPlugin *plugin=qobject_cast<QAbstractPlugin*>(load.instance());
                if(plugin!=NULL)
                {
                    QString type=plugin->getPluginType();
                    QString name=plugin->getPluginName();
                    //只有设置了名称和类型的插件才认为是有效的，否则就会被立马删除释放。
                    if(type!="" && name!="")
                    {
                        QMap<QString,QAbstractPlugin*> plugins=m_plugins.value(type);
                        QAbstractPlugin *pl=plugins.value(name);
                        //如果已经存在相同类型和名称的插件，就把之前的插件删除。
                        if(pl!=NULL)
                        {
                            delete pl;
                        }
                        plugins.insert(name,plugin);
                        m_plugins.insert(type,plugins);

                        //初始化插件
                        plugin->init_plugin();
                    }
                    else
                    {
                        delete plugin;
                    }
                }
            }
        }
    }
    return true;
}

/**
 * @brief 根据插件类型来获取插件
 * @param type--插件类型
 * @return 所有这个类型的插件的集合
 */
QMap<QString,QAbstractPlugin*> PluginLoader::getPluginByType(const QString &type)
{
    return m_plugins.value(type);
}

/**
 * @brief 根据类型和名称来获取插件
 * @param type--插件类型
 * @param name--插件名称
 * @return 查找到的插件，如果没有查找到插件就会返回NULL。
 */
QAbstractPlugin* PluginLoader::getPlugin(const QString &type, const QString &name)
{
    return m_plugins.value(type).value(name);
}

/**
 * @brief 释放全部的插件
 */
void PluginLoader::releasePlugin()
{
    QMapIterator<QString,QMap<QString,QAbstractPlugin*> > it(m_plugins);

    while(it.hasNext())
    {
        it.next();
        QMapIterator<QString,QAbstractPlugin*>  t(it.value());
        while(t.hasNext())
        {
            t.next();
            delete t.value();
        }
    }
    m_plugins.clear();
}
