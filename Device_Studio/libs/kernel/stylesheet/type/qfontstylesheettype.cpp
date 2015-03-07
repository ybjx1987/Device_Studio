#include "qfontstylesheettype.h"

QFontStyleSheetType::QFontStyleSheetType(QAbstractSheetType * parent):
    QAbstractEnumSheetType(parent)
{

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
