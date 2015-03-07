#include "qtextdecorationsheettype.h"

QTextDecorationSheetType::QTextDecorationSheetType(QAbstractSheetType * parent):
    QAbstractEnumSheetType(parent)
{

}

QTextDecorationSheetType::~QTextDecorationSheetType()
{

}

QStringList QTextDecorationSheetType::getValueList()
{
    QStringList list;

    list<<"none"<<"underline"<<"overline"<<"ine-through";

    return list;
}
