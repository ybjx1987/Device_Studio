#include "qrepeatsheettype.h"

QRepeatSheetType::QRepeatSheetType(QAbstractSheetType * parent):
    QAbstractEnumSheetType(parent)
{
    setValue("repeat");
}

QRepeatSheetType::~QRepeatSheetType()
{

}

QStringList QRepeatSheetType::getValueList()
{
    QStringList list;
    list<<"no-repeat"<<"repeat-x"<<"repeat-y"<<"repeat";
    return list;
}
