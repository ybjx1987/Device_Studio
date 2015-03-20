#include "qbordersheettype.h"

#include "qbrushsheettype.h"
#include "qnumbersheettype.h"
#include "qenumsheettype.h"

#include "../../qvarianttype.h"
#include "../../xmlnode.h"
#include "../qsheetpropertyfactory.h"

QBorderSheetType::QBorderSheetType():
    QAbstractSheetType(),
    m_borderStyle(NULL),
    m_borderWidth(NULL),
    m_borderBrush(NULL)
{
    m_borderStyle = new QEnumSheetType();
    m_borderWidth = new QNumberSheetType();
    m_borderBrush = new QBrushSheetType();
    m_borderStyle->setTypeProperty("<Property>"
                                   "<Item>dashed</Item>"
                                   "<Item>dot-dash</Item>"
                                   "<Item>dot-dot-dash</Item>"
                                   "<Item>dotted</Item>"
                                   "<Item>double</Item>"
                                   "<Item>groove</Item>"
                                   "<Item>inset</Item>"
                                   "<Item>outset</Item>"
                                   "<Item>ridge</Item>"
                                   "<Item>solid</Item>"
                                   "<Item>none</Item>"
                                   "</Property>");
}

QBorderSheetType::~QBorderSheetType()
{

}

QString QBorderSheetType::getValueText()
{
    if(!getValue().isValid())
    {
        return "Invalid";
    }

    tagBorderSheetType value = getValue().value<tagBorderSheetType>();

    if(!value.m_borderBrush.m_value.isValid()
            || value.m_borderWidth <=0 || value.m_borderStyle == "")
    {
        return "Invalid";
    }

    return m_borderWidth->getValueText()+" "
            + m_borderStyle->getValueText()+" "
            +m_borderBrush->getValueText();
}

QString QBorderSheetType::getStyleSheetValue()
{
    QString str1,str2,str3;
    str1 = m_borderWidth->getStyleSheetValue();
    str2 = m_borderStyle->getStyleSheetValue();
    str3 = m_borderBrush->getStyleSheetValue();

    if(str1 == "" || str1 == "Invalid" || str2 == ""
            || str2 == "Invalid" || str3 == ""
            || str3 == "Invalid")
    {
        return "";
    }

    return str1 + " " + str2 + " " +str3;
}

QStringList QBorderSheetType::getStyleList()
{
    return m_borderStyle->getValueList();
}

void QBorderSheetType::setValue(const QVariant &value)
{
    tagBorderSheetType v = value.value<tagBorderSheetType>();


    m_borderBrush->setValue(QVariant::fromValue<tagBrushSheetType>(v.m_borderBrush));
    m_borderStyle->setValue(v.m_borderStyle);
    m_borderWidth->setValue(v.m_borderWidth);
    QAbstractSheetType::setValue(value);
}

QEnumSheetType * QBorderSheetType::getBorderStyleProperty()
{
    return m_borderStyle;
}

QBrushSheetType * QBorderSheetType::getBorderBrushProperty()
{
    return m_borderBrush;
}

void QBorderSheetType::toXml(XmlNode *xml)
{
    QAbstractSheetType::toXml(xml);
    XmlNode * obj = new XmlNode(xml);
    m_borderStyle->toXml(obj);
    obj = new XmlNode(xml);
    m_borderWidth->toXml(obj);
    obj = new XmlNode(xml);
    m_borderBrush->toXml(obj);
}

void QBorderSheetType::fromXml(XmlNode *xml)
{
    QAbstractSheetType::fromXml(xml);

    QList<XmlNode*> list = xml->getChildren();

    if(list.size() != 3)
    {
        return ;
    }

    m_borderStyle->fromXml(list.at(0));
    m_borderWidth->fromXml(list.at(1));
    m_borderBrush->fromXml(list.at(2));

    tagBorderSheetType value;
    value.m_borderBrush = m_borderBrush->getValue().value<tagBrushSheetType>();
    value.m_borderStyle = m_borderStyle->getValue().toString();
    value.m_borderWidth = m_borderWidth->getValue().toInt();
    setValue(QVariant::fromValue<tagBorderSheetType>(value));
}

QIcon QBorderSheetType::getValueIcon()
{
    return m_borderBrush->getValueIcon();
}
