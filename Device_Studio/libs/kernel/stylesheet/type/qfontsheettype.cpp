#include "qfontsheettype.h"

#include "qstringsheettype.h"
#include "qlengthsheettype.h"
#include "qfontstylesheettype.h"

#include "../../qvarianttype.h"
#include "../../xmlnode.h"

QFontSheetType::QFontSheetType(QAbstractSheetType * parent):
    QAbstractSheetType(parent)
{

}

QFontSheetType::~QFontSheetType()
{

}

QString QFontSheetType::getValueText()
{
    if(getValue().isValid())
    {
        tagFontSheetType value = getValue().value<tagFontSheetType>();

        QString str;
        str = value.m_style+" "+QString::number(value.m_size)+"px "+value.m_name;
        return str;
    }
    else
    {
        return "Invalid";
    }
}

bool QFontSheetType::toXml(XmlNode *xml)
{
    tagFontSheetType value = getValue().value<tagFontSheetType>();
    xml->setProperty("name",value.m_name);
    xml->setProperty("size",QString::number(value.m_size));
    xml->setProperty("style",value.m_style);
    return QAbstractSheetType::toXml(xml);
}

bool QFontSheetType::fromXml(XmlNode *xml)
{
    tagFontSheetType value;
    value.m_name = xml->getProperty("name");
    value.m_style = xml->getProperty("style");
    value.m_size = xml->getProperty("size").toInt();

    if(value.m_name == "" || value.m_style == ""
            || value.m_size <= 0)
    {
        return false;
    }
    m_value=QVariant::fromValue<tagFontSheetType>(value);
    return QAbstractSheetType::fromXml(xml);
}

bool QFontSheetType::equal(const QVariant &value)
{
    tagFontSheetType v1 = m_value.value<tagFontSheetType>();
    tagFontSheetType v2 = value.value<tagFontSheetType>();

    return (v1 == v2);
}
