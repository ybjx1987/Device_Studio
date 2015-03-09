#ifndef QURLSHEETTYPE_H
#define QURLSHEETTYPE_H

#include "qstringsheettype.h"

#include <QIcon>

class QUrlSheetType : public QStringSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QUrlSheetType(QAbstractSheetType * parent = NULL);
    ~QUrlSheetType();

    QString getValueText();
    QIcon   getValueIcon();

    QString getStyleSheetValue();


};

#endif // QURLSHEETTYPE_H
