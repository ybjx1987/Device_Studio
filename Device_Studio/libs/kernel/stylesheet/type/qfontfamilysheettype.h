#ifndef QFONTFAMILYSHEETTYPE_H
#define QFONTFAMILYSHEETTYPE_H
#include "qabstractenumsheettype.h"

class QFontFamilySheetType : public QAbstractEnumSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QFontFamilySheetType(QAbstractSheetType * parent = NULL);
    ~QFontFamilySheetType();

    QStringList getValueList();
    QString     getValueText();
};

#endif // QFONTFAMILYSHEETTYPE_H
