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
    return QString("url(%1)").arg(getValue().toString());
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
