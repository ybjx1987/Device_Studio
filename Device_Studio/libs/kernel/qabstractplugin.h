#ifndef QABSTRACTPLUGIN_H
#define QABSTRACTPLUGIN_H

#include "kernellibglobal.h"

#include <QString>
#include <QObject>

class KERNEL_EXPORT QPluginInterface
{
public:
    virtual void initPlugin() = 0;
    virtual QString getPluginName() = 0;
    virtual QString getPluginType() = 0;
};


#define QPluginInterface_iid "QPluginInterfaceIID"

Q_DECLARE_INTERFACE(QPluginInterface, QPluginInterface_iid)

class KERNEL_EXPORT QAbstractPlugin : public QObject, public QPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(QPluginInterface)
public:
    virtual void initPlugin();
    virtual QString getPluginName();
    virtual QString getPluginType();
};

#endif // QABSTRACTPLUGIN_H
