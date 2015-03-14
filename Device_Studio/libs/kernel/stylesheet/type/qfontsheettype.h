#ifndef QFONTSHEETTYPE_H
#define QFONTSHEETTYPE_H

#include "qabstractsheettype.h"

class QFontStyleSheetType;
class QLengthSheetType;
class QStringSheetType;

class QFontSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QFontSheetType();
    ~QFontSheetType();

    QString getValueText();
    QString getStyleSheetValue();

    virtual void    toXml(XmlNode * xml);
    virtual void    fromXml(XmlNode * xml);

    virtual bool    equal(const QVariant & value);
};

#endif // QFONTSHEETTYPE_H
