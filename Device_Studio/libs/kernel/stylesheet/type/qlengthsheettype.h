#ifndef QLENGTHSHEETTYPE_H
#define QLENGTHSHEETTYPE_H

#include "qnumbersheettype.h"

class QLengthSheetType : public QNumberSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QLengthSheetType();
    ~QLengthSheetType();


    QString getValueText();
    QString getStyleSheet();
};

#endif // QLENGTHSHEETTYPE_H
