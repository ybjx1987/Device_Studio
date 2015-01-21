#ifndef QHOSTFACTORY_H
#define QHOSTFACTORY_H

#include <QMetaObject>
#include <QMap>
#include <QString>

class QAbstractHost;
class XmlNode;
class QAbstractHostInfo;

/**
 * @brief Host创建类，所有的Host都是使用这个类来创建的，Host不能够直接通过new来创建，降低模块耦合
 */

class QHostFactory
{
public:
    //注册Host，只能够在注册宏中调用
    static void registerHost( QAbstractHostInfo * info);
    //创建一个Host，在需要Host实例的时候调用这个函数
    static QAbstractHost* createHost(const QString& name);
    //获取全部Host的描述列表
    static QList<QAbstractHostInfo*> getHostInfo();
    //获取指定名称的Host的描述内容
    static QAbstractHostInfo*  getHostInfo(const QString &name);
public:
    //存放名称和描述的对应关系
    static QMap<QString,QAbstractHostInfo*>        m_metaMap;
    //存放Host描述列表
    static QList<QAbstractHostInfo*>              m_metas;
};

//注册Host的宏，在每一个新的Host中调用这个宏。
#ifndef qRegisterHost
    #define qRegisterHost(class_name) QHostFactory::registerHost(\
                                                    class_name::getInfo());
#endif

#endif // QHOSTFACTORY_H
