#include "qfontfamilysheettype.h"

#include <QFontDatabase>

QFontFamilySheetType::QFontFamilySheetType(QAbstractSheetType * parent):
    QAbstractEnumSheetType(parent)
{
    setValue("");
}

QFontFamilySheetType::~QFontFamilySheetType()
{

}

QString QFontFamilySheetType::getValueText()
{
    if(m_value.toString() == "")
    {
        return "Invalid";
    }
    else
    {
        return m_value.toString();
    }
}

QStringList QFontFamilySheetType::getValueList()
{
    static QFontDatabase data;
    return data.families();
}
