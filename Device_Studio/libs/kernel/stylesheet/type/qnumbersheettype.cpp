#include "qnumbersheettype.h"

#include "../../xmlnode.h"

QNumberSheetType::QNumberSheetType(QAbstractSheetType * parent):
    QAbstractSheetType(parent),
    m_minValue(0),
    m_maxValue(9999)
{
    setValue(0);
}

QNumberSheetType::~QNumberSheetType()
{

}

QString QNumberSheetType::getValueText()
{
    return QString("%1px").arg(m_value.toInt());
}

void QNumberSheetType::toXml(XmlNode *xml)
{
    xml->setProperty("value",getValue().toString());
    QAbstractSheetType::toXml(xml);
}

void QNumberSheetType::fromXml(XmlNode *xml)
{
    m_value = xml->getProperty("value");
    QAbstractSheetType::fromXml(xml);
}

void QNumberSheetType::parserProperty(XmlNode *xml)
{
    m_minValue = xml->getProperty("minValue").toInt();
    m_maxValue = xml->getProperty("maxValue").toInt();
}

int QNumberSheetType::getMinValue()
{
    return m_minValue;
}

int QNumberSheetType::getMaxValue()
{
    return m_maxValue;
}
