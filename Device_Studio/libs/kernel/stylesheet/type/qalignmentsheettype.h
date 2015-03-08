#ifndef QALIGNMENTSHEETTYPE_H
#define QALIGNMENTSHEETTYPE_H

#include "qabstractenumsheettype.h"

class QAlignmentSheetType : public QAbstractEnumSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QAlignmentSheetType();
    ~QAlignmentSheetType();

    QStringList  getValueList();
};

#endif // QALIGNMENTSHEETTYPE_H
