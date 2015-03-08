#include "qfontstylesheettype.h"

QFontStyleSheetType::QFontStyleSheetType()
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
