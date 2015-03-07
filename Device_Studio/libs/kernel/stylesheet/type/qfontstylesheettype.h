#ifndef QFONTSTYLESHEETTYPE_H
#define QFONTSTYLESHEETTYPE_H

#include "qabstractenumsheettype.h"

class QFontStyleSheetType : public QAbstractEnumSheetType
{
    Q_OBJECT
public:
    QFontStyleSheetType(QAbstractSheetType * parent = NULL);
    ~QFontStyleSheetType();

    QStringList getValueList();
};

#endif // QFONTSTYLESHEETTYPE_H
