#include "qabstractproperty.h"

#include "../xmlnode.h"

#include <QMapIterator>

/**
 * @brief 构造函数
 * @param parent--父节点，如果不为NULL，就会把当前节点添加到父节点的m_children末尾
 */
QAbstractProperty::QAbstractProperty(QAbstractProperty *parent) :
    QObject(parent),
    m_parent(parent)
{
    if(m_parent != NULL)
    {
        m_parent->m_children.append(this);
    }
}

/**
 * @brief 析构函数，同时会冲父节点中删除记录，会删除子节点。
 */
QAbstractProperty::~QAbstractProperty()
{
    if(m_parent != NULL)
    {
        m_parent->m_children.removeAll(this);
    }

    while(m_children.size()>0)
    {
        delete m_children.first();
    }
}

/**
 * @brief 设置属性值，如果属性值发生变化就会发送valueChange()消息
 * @param value--新的属性值
 */
void QAbstractProperty::setValue(const QVariant &value)
{
    if(!this->equal(value))
    {
        m_value = value;
        emit valueChange();
    }
}

/**
 * @brief 设置属性名称
 * @param name--新的属性名称
 */
void QAbstractProperty::setName(const QString &name)
{
    m_propertys.insert("name",name);
}

/**
 * @brief 获取属性名称
 * @return 属性的名称
 */
QString QAbstractProperty::getName()
{
    return m_propertys.value("name");
}

/**
 * @brief 设置属性的默认值
 * @param defaultValue--属性的默认值
 */
void QAbstractProperty::setDefaultValue(const QVariant &defaultValue)
{
    m_defaultValue = defaultValue;
}

/**
 * @brief 获取属性值
 * @return 属性的值
 */
QVariant QAbstractProperty::getValue() const
{
    return m_value;
}

/**
 * @brief 判断属性值是否发生变化
 * @return true--发生了变化，false--没有发生变化
 */
bool QAbstractProperty::isModified()
{
    return !equal(m_defaultValue);
}

/**
 * @brief 根据当前的属性值生成一个xml节点
 * @param xml--存放xml节点的指针，不能为NULL
 * @return true--转换成功，false--转换失败
 */
bool QAbstractProperty::toXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }

    //清空数据，并设置统一的节点标题
    xml->clear();
    xml->setTitle(PROPERTY_TITLE);

    //设置描述符
    QMapIterator<QString,QString>      it(m_propertys);
    while(it.hasNext())
    {
        it.next();
        xml->setProperty(it.key(),it.value());
    }

    //填写属性值
    writeValue();

    XmlNode *subNode;
    //转换子节点
    foreach(QAbstractProperty *property,m_children)
    {
        subNode = new XmlNode(xml);
        if(!property->toXml(subNode))
        {
            xml->clear();
            return false;
        }
    }

    return true;
}

/**
 * @brief 把xml节点转换成属性
 * @param xml--xml节点指针，不能为NULL
 * @return true--转换成功，false--转换失败
 */
bool QAbstractProperty::fromXml(XmlNode *xml)
{
    if(xml == NULL)
    {
        return false;
    }

    //只有指定的标题的才会被进一步的解析
    if(xml->getTitle() != PROPERTY_TITLE)
    {
        return false;
    }

    //转换属性描述符
    QMapIterator<QString,QString>      it(xml->getPropertys());
    while(it.hasNext())
    {
        it.next();
        m_propertys.insert(it.key(),it.value());
    }

    //转换子节点
    QList<XmlNode*> children=xml->getChildren();
    foreach(XmlNode* subNode,children)
    {
        QAbstractProperty *pro=getSubPropertyByName(subNode->getProperty("name"));
        if(pro!=NULL)
        {
            pro->fromXml(subNode);
        }
        else
        {
            return false;
        }
    }

    makeValue();
    return true;
}

/**
 * @brief 把描述符中的value属性转为属性值
 */
void QAbstractProperty::makeValue()
{
    if(m_propertys.keys().contains("value"))
    {
        QVariant v=m_propertys.value("value");
        if(m_value.type()>0)
        {
            v.convert(m_value.type());
        }
        setValue(v);
    }
}

void QAbstractProperty::writeValue()
{
    m_propertys.insert("value",m_value.toString());
}

/**
 * @brief 重载赋值操作符
 * @param property--赋值的属性
 * @return 新的属性
 */
QAbstractProperty & QAbstractProperty::operator =(const QAbstractProperty &property)
{
    this->m_propertys=property.m_propertys;
    QVariant v = property.getValue();
    if(v.type()>0)
    {
        v.convert(m_value.type());
    }
    setValue(v);
    return *this;
}

/**
 * @brief 判断value和当前属性值是否相等
 * @param value--标记的值
 * @return true--相等，false--不相等
 */
bool QAbstractProperty::equal(const QVariant &value)
{
    if(m_value.type() != value.type())
    {
        return false;
    }
    return m_value==value;
}

/**
 * @brief 根据名称获取子节点
 * @param name--子节点的名称
 * @return 子节点指针，如果没有找到就会返回NULL
 */
QAbstractProperty* QAbstractProperty::getSubPropertyByName(const QString &name)
{
    foreach(QAbstractProperty* subProperty,m_children)
    {
        if(subProperty->getName() == name)
        {
            return subProperty;
        }
    }
    return NULL;
}

/**
 * @brief 设置需要保存的标识符
 * @param needSave--新的标识符
 */
void QAbstractProperty::setNeedSave(bool needSave)
{
    m_needSave = needSave;
}

/**
 * @brief 获取需要保存的标准符
 * @return true--需要保存，false--不需要保存
 */
bool QAbstractProperty::getNeedSave()
{
    return m_needSave;
}

/**
 * @brief 还原为默认值
 */
void QAbstractProperty::reset()
{
    setValue(m_defaultValue);
}
