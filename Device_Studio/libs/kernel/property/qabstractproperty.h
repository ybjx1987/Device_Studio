#ifndef QABSTRACTPROPERTY_H
#define QABSTRACTPROPERTY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QIcon>

class XmlNode;

//XML文件中的数据节点标题
#define PROPERTY_TITLE  "Property"

/**
 * @brief 属性的基类，所有的属性都是从这派生出来的。
 */

class QAbstractProperty : public QObject
{
    Q_OBJECT
public:
    //构造函数
    explicit QAbstractProperty(QAbstractProperty *parent = 0);
    //析构函数
    ~QAbstractProperty();
    //设置属性的值
    virtual void    setValue(const QVariant &value);
    //设置属性的默认值
    virtual void    setDefaultValue(const QVariant &defaultValue);
    //获取属性的值
    QVariant getValue() const;
    //获取属性的显示名称
    virtual QString  getShowString()=0;
    //获取属性的显示图标
    virtual QIcon    getShowIcon()=0;
    //获取属性名称
    QString getName();
    //设置属性名称
    void    setName(const QString &name);
    //判断属性的值是否改变
    bool            isModified();
    //根据属性内容生成一个XML节点
    virtual bool    toXml(XmlNode* xml);
    //根据XML节点生成属性的值
    virtual bool    fromXml(XmlNode *xml);
    //重载赋值运行符
    QAbstractProperty & operator=(const QAbstractProperty & property);
    //判断输入的值是否和属性值相等
    virtual bool    equal(const QVariant & value);
    //根据子属性的名称获取子属性
    QAbstractProperty*  getSubPropertyByName(const QString &name);
    //获取需要保存的标记符
    bool                getNeedSave();
    //设置需要保存的标记符
    void                setNeedSave(bool needSave);
    //设置为默认值
    void                reset();

signals:
    //属性值改变时发送这个信号
    void    valueChange();
protected:
    //把属性值写入Property中
    virtual void writeValue();
    //从Property读取值写入当前值
    virtual void makeValue();

protected:
    //父属性
    QAbstractProperty           *m_parent;
    //子属性列表
    QList<QAbstractProperty*>   m_children;
    //属性值
    QVariant                    m_value;
    //属性默认值
    QVariant                    m_defaultValue;
    //属性的描述符
    QMap<QString,QString>       m_propertys;
    //标记这个属性是否需要保存到xml节点中去
    bool                        m_needSave;
};

#endif // QABSTRACTPROPERTY_H
