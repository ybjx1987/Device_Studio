#ifndef QREPEATSHEETTYPE_H
#define QREPEATSHEETTYPE_H

#include "qabstractenumsheettype.h"

class QRepeatSheetType : public QAbstractEnumSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QRepeatSheetType();
    ~QRepeatSheetType();

    QStringList getValueList();
};

#endif // QREPEATSHEETTYPE_H
