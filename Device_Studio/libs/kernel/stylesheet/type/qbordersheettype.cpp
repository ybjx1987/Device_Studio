#include "qbordersheettype.h"

#include "../../qvarianttype.h"
#include "../../xmlnode.h"

QBorderSheetType::QBorderSheetType():
    m_borderWidth(0)
{

}

QBorderSheetType::~QBorderSheetType()
{

}

QString QBorderSheetType::getValueText()
{
    QString str = QBrushSheetType::getValueText();

    if(str == "Invalid")
    {
        return str;
    }

    if(!getStyleList().contains(m_borderStyle) || m_borderWidth <= 0)
    {
        return "Invalid";
    }

    str = QString::number(m_borderWidth)+"px " + m_borderStyle+" "+str;
    return str;
}

QStringList QBorderSheetType::getStyleList()
{
    QStringList list;

    list<<"dashed"<<"dot-dash"<<"dot-dot-dash"<<"dotted"
       <<"double"<<"groove"<<"inset"<<"solid"<<"none";

    return list;
}

QString QBorderSheetType::getStyleSheet()
{
    if(!getValue().isValid() || m_borderStyle == "" || m_borderWidth<=0)
    {
        return "";
    }
    QString str;
    tagBrushSheetType value = getValue().value<tagBrushSheetType>();
    if(value.m_type == "Color")
    {
        QColor c = value.m_value.value<QColor>();
        if(value.m_alpha == "true")
        {
            str = QString("rgb(%1,%2,%3,%4)").arg(c.red())
                    .arg(c.green()).arg(c.blue()).arg(c.alpha());
        }
        else
        {
            str = QString("rgb(%1,%2,%3)").arg(c.red())
                    .arg(c.green()).arg(c.blue());
        }
    }
    else if(value.m_type == "Gradient")
    {
        QGradient g = value.m_value.value<QGradient>();
        if(g.type() == QGradient::NoGradient)
        {
            return "";
        }
        str = styleSheetCode(g);
    }
    else
    {
        return "";
    }

    if(str != "")
    {
        str = m_name + ":" +QString::number(m_borderWidth)+"px "+m_borderStyle+" "+str;
    }
    return str;
}

bool QBorderSheetType::toXml(XmlNode *xml)
{
    QBrushSheetType::toXml(xml);
    xml->setProperty("borderstyle",m_borderStyle);
    xml->setProperty("borderwidth",QString::number(m_borderWidth));
    return true;
}

bool QBorderSheetType::fromXml(XmlNode *xml)
{
    m_borderStyle = xml->getProperty("borderstyle");
    m_borderWidth = xml->getProperty("borderwidth").toInt();
    QBrushSheetType::fromXml(xml);
    return true;
}

void QBorderSheetType::setBorderWidth(int width)
{
    if(m_borderWidth != width)
    {
        m_borderWidth = width;
        emit needUpdate();
    }
}

int QBorderSheetType::getBorderWidth()
{
    return m_borderWidth;
}

void QBorderSheetType::setBorderStyle(const QString &style)
{
    if(m_borderStyle != style)
    {
        m_borderStyle = style;
        emit needUpdate();
    }
}

QString QBorderSheetType::getBorderStyle()
{
    return m_borderStyle;
}
