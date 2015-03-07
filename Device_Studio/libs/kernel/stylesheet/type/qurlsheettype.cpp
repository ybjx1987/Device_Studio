#include "qurlsheettype.h"

QUrlSheetType::QUrlSheetType(QAbstractSheetType * parent):
    QAbstractSheetType(parent)
{

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

QString QUrlSheetType::getStyleSheet()
{
    QString str;
    str=getName()+": url("+getValue().toString()+");";
    return str;
}
