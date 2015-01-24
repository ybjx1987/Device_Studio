#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "kernellibglobal.h"

#include <QMap>

class QAbstractPlugin;

/**
 * @brief 这个类是用来加载插件的，在软件启动的时候调用这个类的相关函数，加载全部的插件。
 */

class KERNEL_EXPORT PluginLoader
{
public:
    //加载插件，根据插件描述文件来加载
    static bool                            loadPlugin(const QString &xml_file_name);
    //获取插件
    static QAbstractPlugin*                getPlugin(const QString &type,const QString &name);
    //根据插件类型获取插件
    static QMap<QString,QAbstractPlugin*>  getPluginByType(const QString &type);
    //删除全部的插件，释放插件内存
    static void                            releasePlugin();
protected:
    //全部的插件指针
    static QMap<QString,QMap<QString,QAbstractPlugin*> >        m_plugins;
};
#endif // PLUGINLOADER_H
