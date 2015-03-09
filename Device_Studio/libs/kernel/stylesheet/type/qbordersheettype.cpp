#include "qbordersheettype.h"

#include "qbrushsheettype.h"
#include "qnumbersheettype.h"
#include "qenumsheettype.h"

#include "../../qvarianttype.h"
#include "../../xmlnode.h"
#include "../qsheetpropertyfactory.h"

QBorderSheetType::QBorderSheetType(QAbstractSheetType * parent):
    QAbstractSheetType(parent),
    m_borderStyle(NULL),
    m_borderWidth(NULL),
    m_borderBrush(NULL)
{
    m_borderStyle = new QEnumSheetType(this);
    m_borderWidth = new QNumberSheetType(this);
    m_borderBrush = new QBrushSheetType(this);
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
    connect(m_borderStyle,SIGNAL(valueChanged(QVariant)),
            this,SLOT(updateValue()));
    connect(m_borderWidth,SIGNAL(valueChanged(QVariant)),
            this,SLOT(updateValue()));
    connect(m_borderBrush,SIGNAL(valueChanged(QVariant)),
            this,SLOT(updateValue()));
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

void QBorderSheetType::updateValue()
{
    tagBorderSheetType v;
    if(m_borderBrush!=NULL)
    {
        v.m_borderBrush = m_borderBrush->getValue().value<tagBrushSheetType>();
    }
    if(m_borderWidth != NULL)
    {
        v.m_borderWidth = m_borderWidth->getValue().toInt();
    }
    if(m_borderStyle != NULL)
    {
        v.m_borderStyle = m_borderStyle->getValue().toString();
    }
    setValue(QVariant::fromValue<tagBorderSheetType>(v));
}
