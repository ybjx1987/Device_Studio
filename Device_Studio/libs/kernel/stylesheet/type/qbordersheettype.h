#ifndef QBORDERSHEETTYPE_H
#define QBORDERSHEETTYPE_H

#include "qabstractsheettype.h"

class XmlNode;
class QEnumSheetType;
class QNumberSheetType;
class QBrushSheetType;

class QBorderSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QBorderSheetType(QAbstractSheetType * parent = NULL);
    ~QBorderSheetType();

    QString getValueText();

    QString getStyleSheetValue();

    QStringList getStyleList();

    void setValue(const QVariant &value);

protected:
    void updateValue();
protected:
    QEnumSheetType       *m_borderStyle;
    QNumberSheetType     *m_borderWidth;
    QBrushSheetType      *m_borderBrush;
};

#endif // QBORDERSHEETTYPE_H
