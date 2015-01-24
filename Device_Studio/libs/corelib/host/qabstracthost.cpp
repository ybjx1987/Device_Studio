#include "qabstracthost.h"

#include "../xmlnode.h"
#include "../qhostfactory.h"
#include "../property/qabstractproperty.h"

#include <QUuid>

#define ABSTRACT_HOST_OBJECT "Object"

//通用描述符
QAbstractHostInfo * QAbstractHost::m_info = NULL;

/**
 * @brief 构造函数
 * @param parent--父Host
 */
QAbstractHost::QAbstractHost(QAbstractHost *parent) :
    QObject(parent),
    m_parent(parent),
    m_object(NULL)
{
    if(m_parent != NULL)
    {
        m_parent->m_children.append(this);
    }
}

/**
 * @brief 析构函数
 */
QAbstractHost::~QAbstractHost()
{
    if(m_parent != NULL)
    {
        m_parent->m_children.removeAll(this);
    }

    while(m_children.size()>0)
    {
        delete m_children.first();
    }

    if(m_object != NULL)
    {
        delete m_object;
    }
}

/**
 * @brief 获取父Host
 * @return 父Host
 */
QAbstractHost* QAbstractHost::getParent()
{
    return m_parent;
}

/**
 * @brief 设置父Host，同时会处理原父Host和先父Host中的子列表的内容
 * @param parent--新的父Host指针
 */
void QAbstractHost::setParent(QAbstractHost *parent)
{
    if(m_parent != parent)
    {
        if(m_parent != NULL)
        {
            m_parent->m_children.removeAll(this);
        }
        m_parent = parent;
        if(m_parent != NULL)
        {
            m_parent->m_children.append(this);
        }
        emit parentChange();
    }
}

/**
 * @brief 获取指定位置的子Host
 * @param index--子Host的索引
 * @return 找到时返回相应的指针，否则返回NULL
 */
QAbstractHost* QAbstractHost::getChild(int index)
{
    if(index < 0 || index >= m_children.size() )
    {
        return NULL;
    }
    else
    {
        return m_children.at(index);
    }
}

/**
 * @brief 获取全部的子Host
 * @return 全部的子Host
 */
QList<QAbstractHost*> QAbstractHost::getChildren()
{
    return m_children;
}

/**
 * @brief 插入子Host
 * @param child--需要插入的Host
 * @param index--需要插入的位置，如果插入的位置超出了范围，就会直接添加到末尾
 */
void QAbstractHost::insertChildren(QAbstractHost *child, int index)
{
    if(index < 0 || index >= m_children.size())
    {
        index = m_children.size();
    }
    if(m_children.indexOf(child) < 0)
    {
        m_children.removeAll(child);
    }
    if(child->getParent() != this)
    {
        child->setParent(this);
    }
    m_children.insert(index,child);
}

/**
 * @brief 移除子Host
 * @param child--需要移除的Host
 */
void QAbstractHost::removeChildren(QAbstractHost *child)
{
    m_children.removeAll(child);
}

/**
 * @brief 获取子Host的个数
 * @return 子Host的个数
 */
int QAbstractHost::getChildrenCount()
{
    return m_children.size();
}

/**
 * @brief 获取Object
 * @return Object的指针
 */
QObject* QAbstractHost::getObject()
{
    return m_object;
}

/**
 * @brief 设置Object
 * @param object--新的object
 */
void QAbstractHost::setObject(QObject *object)
{
    if(object != m_object)
    {
        if(m_object != NULL)
        {
            delete m_object;
        }
        m_object = object;
    }
}

/**
 * @brief 创建一个新的object，派生类需要重写这个函数
 */
void QAbstractHost::createObject()
{
    m_object = NULL;
}

/**
 * @brief 获取全部的属性
 * @return 属性列表
 */
QList<QAbstractProperty*> QAbstractHost::getPropertys()
{
    return m_propertys;
}

/**
 * @brief 根据属性名称获取属性
 * @param name--属性的名称
 * @return 如果找到这个属性就返回相应的指针，否则返回NULL
 */
QAbstractProperty* QAbstractHost::getProperty(const QString &name)
{
    foreach(QAbstractProperty* property,m_propertys)
    {
        if(property->getName() == name)
        {
            return property;
        }
    }
    return NULL;
}

/**
 * @brief Host的初始化
 * @return true--初始化成功，false--初始化失败
 */
bool QAbstractHost::init()
{
    createObject();
    if(m_object == NULL)
    {
        return false;
    }
    initProperty();
    return true;
}

/**
 * @brief 初始化属性
 */
void QAbstractHost::initProperty()
{

}

/**
 * @brief 获取类型组
 * @return 类型组
 */
QString QAbstractHost::getGroup()
{
    return ABSTRACT_HOST_OBJECT;
}

/**
 * @brief 把当前Host转换为xml节点
 * @param xml--xml节点指针，不能为空
 * @return true--转换成功，false--转换失败
 */
bool QAbstractHost::toXml(XmlNode *xml)
{
    if(xml!=NULL)
    {
        xml->clear();

        xml->setTitle(getGroup());

        QMapIterator<QString,QString>       it(m_attributes);
        while(it.hasNext())
        {
            it.next();
            xml->setProperty(it.key(),it.value());
        }

        XmlNode* proXml;
        foreach(QAbstractProperty* pro,m_propertys)
        {
            if(pro->isModified() || pro->getNeedSave())
            {
                proXml=new XmlNode(xml);
                if(!pro->toXml(proXml))
                {
                    xml->clear();
                    return false;
                }
            }
        }

        foreach(QAbstractHost* child,m_children)
        {
            proXml=new XmlNode(xml);
            if(!child->toXml(proXml))
            {
                xml->clear();
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief 根据xml节点构建Host
 * @param xml--xml节点指针
 * @return true--转换成功，false-转换失败
 */
bool QAbstractHost::fromXml(XmlNode *xml)
{
    if(xml!=NULL)
    {
        if(xml->getTitle()!=getGroup())
        {
            return false;
        }

        clear();

        QMapIterator<QString,QString>       it(m_attributes);
        while(it.hasNext())
        {
            it.next();
            m_attributes.insert(it.key(),xml->getProperty(it.key()));
        }

        if(getAttribute("uuid")=="")
        {
            setAttribute("uuid",QUuid::createUuid().toString());
        }

        QList<XmlNode*>   children=xml->getChildren();
        foreach(XmlNode* obj,children)
        {
            if(obj->getTitle()==PROPERTY_TITLE)
            {
                QAbstractProperty *pro = getProperty(obj->getProperty("name"));
                pro->fromXml(obj);
                pro->setNeedSave(true);
            }
            else
            {
                QString hostType=obj->getProperty("type");

                QAbstractHost *h=QHostFactory::createHost(hostType);
                if(h!=NULL)
                {
                    h->fromXml(obj);
                    h->setParent(this);
                }
                else
                {
                    xml->clear();
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief 清空Host，会清空全部的子Host，会删除Object，会复位属性的值
 */
void QAbstractHost::clear()
{
    while(m_children.size()>0)
    {
        delete m_children.first();
    }

    if(m_object != NULL)
    {
        delete m_object;
        m_object = NULL;
    }

    foreach(QAbstractProperty* property,m_propertys)
    {
        property->reset();
    }
}

/**
 * @brief 设置描述符
 * @param key--键
 * @param value--值
 */
void QAbstractHost::setAttribute(const QString &key, const QString &value)
{
    m_attributes.insert(key,value);
}

/**
 * @brief 获取描述符的值
 * @param key--键
 * @param def--默认值
 * @return 如果找到就返回相应的值，如果没有找到就返回默认值(def)
 */
QString QAbstractHost::getAttribute(const QString &key, const QString &def)
{
    return m_attributes.value(key,def);
}

/**
 * @brief 获取通用的描述符
 * @return 通用描述符指针
 */
QAbstractHostInfo* QAbstractHost::getInfo()
{
    return m_info;
}
