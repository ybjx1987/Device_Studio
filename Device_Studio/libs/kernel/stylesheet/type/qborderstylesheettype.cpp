#include "qborderstylesheettype.h"

QBorderStyleSheetType::QBorderStyleSheetType(QAbstractSheetType * parent):
    QAbstractEnumSheetType(parent)
{
    setValue("none");
}

QBorderStyleSheetType::~QBorderStyleSheetType()
{

}

QStringList QBorderStyleSheetType::getValueList()
{
    QStringList list;

    list<<"dashed"<<"dot-dash"<<"dot-dot-dash"<<"dotted"
       <<"double"<<"groove"<<"inset"<<"solid"<<"none";

    return list;
}
