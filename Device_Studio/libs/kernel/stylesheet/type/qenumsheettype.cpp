#include "qenumsheettype.h"

#include "../../xmlnode.h"

QEnumSheetType::QEnumSheetType(QAbstractSheetType * parent):
    QAbstractSheetType(parent)
{
    setValue("");
}

QEnumSheetType::~QEnumSheetType()
{

}

void QEnumSheetType::fromXml(XmlNode *xml)
{
    m_value = xml->getProperty("value");
    QAbstractSheetType::fromXml(xml);
}

void QEnumSheetType::toXml(XmlNode *xml)
{
    xml->setProperty("value",getValue().toString());
    QAbstractSheetType::toXml(xml);
}

QString QEnumSheetType::getValueText()
{
    if(m_value.toString() == "")
    {
        return "Invalid";
    }
    else
    {
        return m_value.toString();
    }
}

QStringList QEnumSheetType::getValueList()
{
    return m_valueList;
}

void QEnumSheetType::parserProperty(XmlNode *xml)
{
    foreach(XmlNode * obj,xml->getChildren())
    {
        m_valueList.append(obj->getText());
    }
}
