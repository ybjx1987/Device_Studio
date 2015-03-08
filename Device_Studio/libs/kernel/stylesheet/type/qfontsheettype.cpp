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

        if(value.m_style != "")
        {
            str = value.m_style;
        }
        if(value.m_size > 0)
        {
            if(str != "")
            {
                str += " ";
            }
            str += (QString::number(value.m_size)+"px");
        }
        if(value.m_name != "")
        {
            if(str != "")
            {
                str += " ";
            }
            str += ( "\""+value.m_name+"\"");
        }
        return str;
    }
    else
    {
        return "Invalid";
    }
}

QString QFontSheetType::getStyleSheet()
{
    QString ret = getValueText();
    if(ret == "Invalid")
    {
        return "";
    }
    else
    {
        return (m_name+" : "+ret);
    }
}

bool QFontSheetType::toXml(XmlNode *xml)
{
    tagFontSheetType value = getValue().value<tagFontSheetType>();
    xml->setProperty("name",value.m_name);
    xml->setProperty("size",QString::number(value.m_size));
    xml->setProperty("style",value.m_style);
    xml->setTitle("Property");
    xml->setProperty("type",getName());
    xml->setProperty("enabled",m_enabled?"true":"false");

    return true;
}

bool QFontSheetType::fromXml(XmlNode *xml)
{
    tagFontSheetType value;
    value.m_name = xml->getProperty("name");
    value.m_style = xml->getProperty("style");
    value.m_size = xml->getProperty("size").toInt();
    m_enabled = xml->getProperty("enabled") =="true";

    if(value.m_name == "" && value.m_style == ""
            && value.m_size <= 0)
    {
        m_value = QVariant();
    }
    else
    {
        m_value=QVariant::fromValue<tagFontSheetType>(value);
    }
    return true;
}

bool QFontSheetType::equal(const QVariant &value)
{
    tagFontSheetType v1 = m_value.value<tagFontSheetType>();
    tagFontSheetType v2 = value.value<tagFontSheetType>();

    return (v1 == v2);
}
