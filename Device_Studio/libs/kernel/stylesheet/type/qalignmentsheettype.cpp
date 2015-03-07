#include "qalignmentsheettype.h"

QAlignmentSheetType::QAlignmentSheetType(QAbstractSheetType * parent):
    QAbstractEnumSheetType(parent)
{
    setValue("left center");
}

QAlignmentSheetType::~QAlignmentSheetType()
{

}

QStringList QAlignmentSheetType::getValueList()
{
    QStringList list;

    list<<"left top"<<"left center"<<"left bottom"
       <<"center top"<<"center"<<"center bottom"
      <<"right top"<<"right center"<<"right bottom";
    return list;
}
