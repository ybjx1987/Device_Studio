#include "pluginloader.h"

#include "qabstractplugin.h"
#include "xmlnode.h"

#include <QApplication>
#include <QPluginLoader>
#include <QDir>

QMap<QString,QMap<QString,QAbstractPlugin*> > PluginLoader::m_plugins;

void PluginLoader::loadPlugin(const QString &xml_file_name)
{
    XmlNode xml;
    QFile f(xml_file_name);
    if(f.open(QFile::ReadOnly))
    {
        QString str = f.readAll();
        xml.load(str);
        f.close();
    }

    if(xml.getTitle() != "Plugin")
    {
        xml.clear();
        xml.setTitle("Plugin");
        XmlNode *t ;
        t=new XmlNode(&xml);
        t->setTitle("Path");
        t->setProperty("path","pages");
    }

    if(xml.getTitle() == "Plugin")
    {
        QList<XmlNode*> paths = xml.getChildren();
        QString path = QApplication::applicationDirPath();
        foreach(XmlNode * node,paths)
        {
            QString p = path + "/" +node->getProperty("path");
            QDir dir(p);
            QFileInfoList list = dir.entryInfoList(QDir::Files);
            for(int i= 0; i<list.size();i++)
            {
                QPluginLoader load(list.at(i).filePath());
                if(load.load())
                {
                    QAbstractPlugin * plugin = qobject_cast<QAbstractPlugin*>(load.instance());
                    if(plugin != NULL)
                    {
                        QString type = plugin->getPluginType();
                        QString name = plugin->getPluginName();
                        if(type != "" && name != "")
                        {
                            QMap<QString,QAbstractPlugin*> plugins = m_plugins.value(type);
                            QAbstractPlugin *pl = plugins.value(name);
                            if(pl != NULL)
                            {
                                delete pl;
                            }
                            plugins.insert(name,plugin);
                            m_plugins.insert(type,plugins);
                            plugin->initPlugin();
                        }
                        else
                        {
                            delete plugin;
                        }
                    }
                }
                else
                {
                    qDebug(load.errorString().toLocal8Bit());
                }
            }
        }
    }
}

QMap<QString,QAbstractPlugin*>  PluginLoader::getPluginByType(const QString &type)
{
    return m_plugins.value(type);
}
