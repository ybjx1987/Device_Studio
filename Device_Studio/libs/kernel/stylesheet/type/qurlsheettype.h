#ifndef QURLSHEETTYPE_H
#define QURLSHEETTYPE_H

#include "qabstractsheettype.h"

#include <QIcon>

class QUrlSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QUrlSheetType(QAbstractSheetType * parent = NULL);
    ~QUrlSheetType();

    QString getValueText();
    QIcon   getValueIcon();

    QString getStyleSheet();
};

#endif // QURLSHEETTYPE_H
