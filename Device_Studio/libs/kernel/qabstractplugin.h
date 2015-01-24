#ifndef QABSTRACTPLUGIN_H
#define QABSTRACTPLUGIN_H

#include "kernellibglobal.h"

#include <QString>
#include <QObject>

/**
 * @brief 插件接口基类，所有的插件接口都是从这里派生出来的。
 */

class KERNEL_EXPORT QPluginInterface
{
public:
    //插件初始化
    virtual void        initPlugin()=0;
    //获取插件名称
    virtual QString     getPluginName()=0;
    //获取插件类型
    virtual QString     getPluginType()=0;
};

#define QPluginInterface_iid "QPluginInterfaceIID"

Q_DECLARE_INTERFACE(QPluginInterface, QPluginInterface_iid)

/**
 * @brief 插件的基类，全部的插件都是从这里派生出来的。
 */

class KERNEL_EXPORT QAbstractPlugin : public QObject,public QPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(QPluginInterface)
public:
    //插件初始化
    void initPlugin();
    //获取插件名称
    QString getPluginName();
    //获取插件类型
    QString getPluginType();
};

#endif // QABSTRACTPLUGIN_H
