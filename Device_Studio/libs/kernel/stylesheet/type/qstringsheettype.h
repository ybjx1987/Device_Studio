#ifndef QSTRINGSHEETTYPE_H
#define QSTRINGSHEETTYPE_H

#include "qabstractsheettype.h"

class QStringSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QStringSheetType();
    ~QStringSheetType();
};

#endif // QSTRINGSHEETTYPE_H
