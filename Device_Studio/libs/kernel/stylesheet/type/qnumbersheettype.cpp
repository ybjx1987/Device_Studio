#include "qnumbersheettype.h"

#include "../../xmlnode.h"

QNumberSheetType::QNumberSheetType():
    m_type("Integer")
{
    setValue(0);
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
    if(m_type != type)
    {
        m_type = type;
        emit needUpdate();
    }
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

