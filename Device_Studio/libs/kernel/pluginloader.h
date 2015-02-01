#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "kernellibglobal.h"

#include <QMap>

class QAbstractPlugin;
class KERNEL_EXPORT PluginLoader
{
public:
    //页面插件操作
    static void                            loadPlugin(const QString &xml_file_name);
    static QMap<QString,QAbstractPlugin*>  getPluginByType(const QString &type);
protected:
    static QMap<QString,QMap<QString,QAbstractPlugin*> >        m_plugins;
};

#endif // PLUGINLOADER_H
