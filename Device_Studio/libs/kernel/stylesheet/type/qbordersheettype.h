#ifndef QBORDERSHEETTYPE_H
#define QBORDERSHEETTYPE_H

#include "qabstractsheettype.h"

#include <QIcon>

class XmlNode;
class QEnumSheetType;
class QNumberSheetType;
class QBrushSheetType;

class QBorderSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QBorderSheetType();
    ~QBorderSheetType();

    QString getValueText();
    QIcon   getValueIcon();

    QString getStyleSheetValue();

    QStringList getStyleList();

    void setValue(const QVariant &value);

    QEnumSheetType  * getBorderStyleProperty();
    QBrushSheetType * getBorderBrushProperty();

    void toXml(XmlNode *xml);
    void fromXml(XmlNode *xml);
protected:
    QEnumSheetType       *m_borderStyle;
    QNumberSheetType     *m_borderWidth;
    QBrushSheetType      *m_borderBrush;
};

#endif // QBORDERSHEETTYPE_H
