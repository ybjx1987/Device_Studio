#include "qlengthsheettype.h"

QLengthSheetType::QLengthSheetType(QAbstractSheetType * parent):
    QNumberSheetType(parent)
{
    setType("Integer");
}

QLengthSheetType::~QLengthSheetType()
{

}

QString QLengthSheetType::getValueText()
{
    return QNumberSheetType::getValueText()+" px";
}

QString QLengthSheetType::getStyleSheet()
{
    QString str;
    str = getName() +":"+getValueText();
    return str;
}
