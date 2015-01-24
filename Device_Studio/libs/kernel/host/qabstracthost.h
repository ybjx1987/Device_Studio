#ifndef QABSTRACTHOST_H
#define QABSTRACTHOST_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QMetaObject>

class XmlNode;
class QAbstractProperty;

/**
 * @brief Host的描述基类，
 */

class QAbstractHostInfo
{
public:
    //Host名称
    QString     m_name;
    //Host类别
    QString     m_group;
    //Host的元类型
    QMetaObject  *m_metaObject;
    //Host的索引
    int         m_index;
};

/**
 * @brief Host基类，所有的Host都是从这里派生出来的。
 */
class QAbstractHost : public QObject
{
    Q_OBJECT
public:
    //构造函数
    explicit QAbstractHost(QAbstractHost *parent = 0);
    //析构函数
    ~QAbstractHost();
    //获取父Host
    QAbstractHost   *getParent();
    //设置父Host
    void            setParent(QAbstractHost*    parent);
    //获取子Host
    QAbstractHost*  getChild(int index);
    //获取全部的子Host
    QList<QAbstractHost*>   getChildren();
    //插入子Host
    void            insertChildren(QAbstractHost* child,int index = -1);
    //移除子Host
    void            removeChildren(QAbstractHost* child);
    //获取子Host的个数
    int             getChildrenCount();
    //获取Object
    QObject*        getObject();
    //设置Object
    void            setObject(QObject* object);
    //初始化Host，在HostFactory中调用
    bool            init();
    //获取全部的属性
    QList<QAbstractProperty*>   getPropertys();
    //根据名称获取属性
    QAbstractProperty*          getProperty(const QString &name);
    //根据属性值构建xml节点
    virtual bool    toXml(XmlNode *xml);
    //根据xml节点构建Host
    virtual bool    fromXml(XmlNode *xml);
    //获取Host的类型组
    virtual QString getGroup();
    //清空Host的全部内容
    void            clear();
    //设置Host描述符
    void            setAttribute(const QString &key,const QString &value);
    //获取Host描述符
    QString         getAttribute(const QString &key,const QString &def = "");
    //获取Host的通用描述符
    static QAbstractHostInfo* getInfo();
protected:
    //创建Object
    virtual void    createObject();
    //初始化属性
    virtual void    initProperty();
signals:
    //符Host发生变化的信号
    void    parentChange();
protected:
    //父Host
    QAbstractHost           *m_parent;
    //子Host列表
    QList<QAbstractHost*>   m_children;
    //需要描述的Object
    QObject                 *m_object;
    //属性列表
    QList<QAbstractProperty*>   m_propertys;
    //描述符表
    QMap<QString,QString>       m_attributes;
    //通用描述符
    static QAbstractHostInfo    *m_info;
};

#endif // QABSTRACTHOST_H
