#ifndef QFONTFAMILYSHEETTYPE_H
#define QFONTFAMILYSHEETTYPE_H
#include "qabstractenumsheettype.h"

class QFontFamilySheetType : public QAbstractEnumSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QFontFamilySheetType();
    ~QFontFamilySheetType();

    QStringList getValueList();
    QString     getValueText();
    QString     getStyleSheet();
};

#endif // QFONTFAMILYSHEETTYPE_H
