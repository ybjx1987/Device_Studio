#include "qurlsheettype.h"

QUrlSheetType::QUrlSheetType(QAbstractSheetType * parent):
    QStringSheetType(parent)
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
        return QString("url(%1)").arg(getValue().toString());
    }
    else
    {
        return "None";
    }
}

QIcon QUrlSheetType::getValueIcon()
{
    QIcon icon(getValue().toString());
    return icon;
}

QString QUrlSheetType::getStyleSheetValue()
{
    if(getValue().toString() != "")
    {
        QString str;
        str="url("+getValue().toString()+")";
        return str;
    }
    else
    {
        return "";
    }
}
