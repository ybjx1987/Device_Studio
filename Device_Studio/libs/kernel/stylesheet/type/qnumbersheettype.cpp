#include "qnumbersheettype.h"

#include "../../xmlnode.h"

QNumberSheetType::QNumberSheetType(QAbstractSheetType * parent):
    QAbstractSheetType(parent),
    m_type("Integer")
{
}

QNumberSheetType::~QNumberSheetType()
{

}

QString QNumberSheetType::getValueText()
{
    QString str;
    if(m_type == "Integer")
    {
        str.sprintf("%d",getValue().toInt());
    }
    else if(m_type == "Float")
    {
        str.sprintf("%f",getValue().toFloat());
    }
    return str;
}

QString QNumberSheetType::getType()
{
    return m_type;
}

void QNumberSheetType::setType(const QString &type)
{
    m_type = type;
}

bool QNumberSheetType::toXml(XmlNode *xml)
{
    xml->setProperty("type",m_type);
    return QAbstractSheetType::toXml(xml);
}

bool QNumberSheetType::fromXml(XmlNode *xml)
{
    m_type = xml->getProperty("type");
    return QAbstractSheetType::fromXml(xml);
}

