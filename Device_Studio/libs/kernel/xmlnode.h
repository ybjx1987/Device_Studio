#ifndef XMLNODE_H
#define XMLNODE_H

#include "kernellibglobal.h"

#include <QList>
#include <QString>
#include <QMap>

class QXmlStreamReader;
class QXmlStreamWriter;

class KERNEL_EXPORT XmlNode
{
public:
    //构造函数
    XmlNode(XmlNode* parent=NULL);
    //析构函数
    ~XmlNode();

    //获取父节点
    XmlNode*        getParent();
    //获取指定索引的子节点
    XmlNode*        getAt(int index);
    //获取子节点的个数
    int             getChildrenCount();
    //获取全部的子节点
    QList<XmlNode*> getChildren();
    //清空节点信息，主要是清空子节点和节点属性
    void            clear();

    //通过一个字符串路径来生成一个节点信息
    bool            load(const QString &buffer);
    //通过reader来生成一个节点信息
    bool            load(QXmlStreamReader *reader);
    //把当前节点信息保存为字符串
    bool            save(QString &buffer);
    //把当前节点信息保存到writer
    bool            save(QXmlStreamWriter *writer);

    //获取节点标题
    QString         getTitle();
    //设置该节点的标题
    void            setTitle(const QString &title);

    //获取节点文本
    QString         getText();
    //设置节点文本
    void            setText(const QString &text);

    //设置节点属性
    void            setProperty(const QString &key,const QString &value);
    //获取节点属性
    QString         getProperty(const QString &key,const QString &def = "");
    //获取全部的属性
    QMap<QString,QString>   getPropertys();
protected:
    //子节点列表
    QList<XmlNode*>     m_children;
    //父节点
    XmlNode*            m_parent;

    //节点标题
    QString             m_title;
    //节点文本
    QString             m_text;
    //节点属性
    QMap<QString,QString> m_property;
};

#endif // XMLNODE_H
