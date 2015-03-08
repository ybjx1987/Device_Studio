#include "qlengthsheettype.h"

QLengthSheetType::QLengthSheetType()
{
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
