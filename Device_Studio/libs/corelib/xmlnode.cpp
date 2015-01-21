#include "xmlnode.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

/**
 * @brief 构造函数
 * @param parent--父节点，如果没有父节点则为NULL
 */
XmlNode::XmlNode(XmlNode* parent):
    m_parent(parent)
{
    if(m_parent != NULL)
    {
        m_parent->m_children.append(this);
    }
}

/**
 * @brief 西沟函数，删除子节点，释放子节点的内存。
 */
XmlNode::~XmlNode()
{
    if(m_parent != NULL)
    {
        m_parent->m_children.removeAll(this);
        m_parent = NULL;
    }
    while(m_children.size()>0)
    {
        delete m_children.first();
    }
}

/**
 * @brief 获取父节点
 * @return 返回父节点指针
 */
XmlNode* XmlNode::getParent()
{
    return m_parent;
}

/**
 * @brief 获取子节点的个数
 * @return 子节点个数
 */
int XmlNode::getChildrenCount()
{
    return m_children.size();
}

/**
 * @brief 获取指定位置的子节点
 * @param index--子节点的索引
 * @return 子节点指针，如果输入的索引小于0或大于等于子节点个数将会返回NULL
 */
XmlNode* XmlNode::getAt(int index)
{
    if(index <0 || m_children.size()<=index)
    {
        return NULL;
    }
    else
    {
        return m_children.at(index);
    }
}

/**
 * @brief 获取子节点列表
 * @return 子节点列表
 */
QList<XmlNode*> XmlNode::getChildren()
{
    return m_children;
}

/**
 * @brief 清空节点信息，包括全部的子节点、节点属性、节点文本、节点标题。
 */
void XmlNode::clear()
{
    while(m_children.size()>0)
    {
        delete m_children.first();
    }
    m_property.clear();
    m_title = "";
    m_text = "";
}

/**
 * @brief 加载XML文本
 * @param 具有XML格式的文本内容，必须只有一个根节点
 * @return 如果解析成功就返回true，如果解析失败就返回false
 */
bool XmlNode::load(const QString &buffer)
{
    QXmlStreamReader reader(buffer);
    while(!reader.atEnd())
    {
        if(reader.readNext()==QXmlStreamReader::StartElement)
        {
            return load(&reader);
        }
    }
    return false;
}

/**
 * @brief 根据reader来解析XML文本
 * @param reader--XML文本的读取器
 * @return 如果解析成功就返回true，如果失败就返回false
 */
bool XmlNode::load(QXmlStreamReader *reader)
{
    clear();
    setTitle(reader->name().toString());
    foreach(QXmlStreamAttribute attr,reader->attributes())
    {
        setProperty(attr.name().toString(),attr.value().toString());
    }
    bool b=true;
    while(b && !reader->hasError())
    {
        switch(reader->readNext())
        {
        case QXmlStreamReader::StartElement:
        {
            XmlNode *xml=new XmlNode(this);
            xml->load(reader);
        }
            break;
        case QXmlStreamReader::EndElement:
            b=false;
            break;
        case QXmlStreamReader::Characters:
            m_text=reader->text().toString();
            break;
        default:
            break;
        }
    }
}

/**
 * @brief 保存当前节点信息到文本中去
 * @param buffer--保存的文本
 * @return 如果保存成功就返回true，如果保存失败就返回false
 */
bool XmlNode::save(QString &buffer)
{
    QString str = "";
    QXmlStreamWriter writer(str);
    writer.writeStartDocument();
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(1);
    if(!save(&writer))
    {
        return false;
    }
    writer.writeEndDocument();
    buffer = str;
    return true;
}

/**
 * @brief 保存当前节点的信息到XML的写入器中去
 * @param writer--XML写入器
 * @return 如果写入成功就返回true，如果写入失败就返回false
 */
bool XmlNode::save(QXmlStreamWriter *writer)
{
    if(m_title=="")
    {
        return false;
    }
    writer->writeStartElement(m_title);

    QMapIterator<QString,QString> it(m_property);
    while(it.hasNext())
    {
        it.next();
        writer->writeAttribute(it.key(),it.value());
    }

    if(m_text != "")
    {
        writer->writeCharacters(m_text);
    }

    foreach(XmlNode* xml,m_children)
    {
        if(!xml->write(writer))
        {
            return false;
        }
    }

    writer->writeEndElement();
    return true;
}

/**
 * @brief 获取节点标题
 * @return 节点标题
 */
QString XmlNode::getTitle()
{
    return m_title;
}

/**
 * @brief 设置节点标题
 * @param title--新的节点标题
 */
void XmlNode::setTitle(const QString &title)
{
    m_title = title;
}

/**
 * @brief 获取节点文本
 * @return 节点文本
 */
QString XmlNode::getText()
{
    return m_text;
}

/**
 * @brief 设置节点文本
 * @param text--新的节点文本
 */
void XmlNode::setText(const QString &text)
{
    m_text = text;
}

/**
 * @brief 设置节点属性
 * @param key--属性的关键字
 * @param value--属性的值
 */
void XmlNode::setProperty(const QString &key, const QString &value)
{
    m_property.insert(key,value);
}

/**
 * @brief 获取节点属性
 * @param key--属性的关键字
 * @param def--属性的默认值，如果没有找到这个属性就会直接返回这个值
 * @return 属性的值
 */
QString XmlNode::getProperty(const QString &key, const QString &def)
{
    return m_property.value(key,def);
}

/**
 * @brief 获取全部的属性
 * @return 全部的属性
 */
QMap<QString,QString> XmlNode::getPropertys()
{
    return m_property;
}
