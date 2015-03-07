#include "qstringsheettype.h"

QStringSheetType::QStringSheetType(QAbstractSheetType * parent):
    QAbstractSheetType(parent)
{
    setValue("");
}

QStringSheetType::~QStringSheetType()
{

}

