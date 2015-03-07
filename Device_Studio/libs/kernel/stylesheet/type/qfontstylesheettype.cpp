#include "qfontstylesheettype.h"

QFontStyleSheetType::QFontStyleSheetType(QAbstractSheetType * parent):
    QAbstractEnumSheetType(parent)
{
    setValue("normal");
}

QFontStyleSheetType::~QFontStyleSheetType()
{

}

QStringList QFontStyleSheetType::getValueList()
{
    QStringList list;

    list<<"normal"<<"italic";

    return list;
}
