#include "qtextdecorationsheettype.h"

QTextDecorationSheetType::QTextDecorationSheetType()
{
    setValue("none");
}

QTextDecorationSheetType::~QTextDecorationSheetType()
{

}

QStringList QTextDecorationSheetType::getValueList()
{
    QStringList list;

    list<<"none"<<"underline"<<"overline"<<"line-through";

    return list;
}
