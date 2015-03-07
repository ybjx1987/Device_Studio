#ifndef QABSTRACTENUMSHEETTYPE_H
#define QABSTRACTENUMSHEETTYPE_H

#include "qabstractsheettype.h"

class QAbstractEnumSheetType: public QAbstractSheetType
{
public:
    QAbstractEnumSheetType(QAbstractSheetType * parent = NULL);
    ~QAbstractEnumSheetType();

    virtual QStringList  getValueList() = 0;
};

#endif // QABSTRACTENUMSHEETTYPE_H
