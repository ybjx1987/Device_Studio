#ifndef QSTRINGSHEETTYPE_H
#define QSTRINGSHEETTYPE_H

#include "qabstractsheettype.h"

class QStringSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QStringSheetType();
    ~QStringSheetType();

    QString getValueText();

    void toXml(XmlNode *xml);
    void fromXml(XmlNode *xml);
};

#endif // QSTRINGSHEETTYPE_H
