#include "qurlsheettype.h"

QUrlSheetType::QUrlSheetType():
    QStringSheetType()
{
    setValue("");
}

QUrlSheetType::~QUrlSheetType()
{

}

QString QUrlSheetType::getValueText()
{
    if(getValue().toString() != "")
    {
        return QString("%1").arg(getValue().toString());
    }
    else
    {
        return "Invalid";
    }
}

QIcon QUrlSheetType::getValueIcon()
{
    if(getValue().toString() != "")
    {
        QString str = ":/project/"+m_type+"/"+getValue().toString();
        QIcon icon(str);
        return icon;
    }
    else
    {
        return QIcon();
    }
}

QString QUrlSheetType::getStyleSheetValue()
{
    if(getValue().toString() != "")
    {
        QString str;
        str="url(:/project/"+m_type+"/"+getValue().toString()+")";
        return str;
    }
    else
    {
        return "";
    }
}
