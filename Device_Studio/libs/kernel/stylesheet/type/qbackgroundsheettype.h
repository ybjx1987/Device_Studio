#ifndef QBACKGROUNDSHEETTYPE_H
#define QBACKGROUNDSHEETTYPE_H

#include "qabstractsheettype.h"

#include <QIcon>

class QBrushSheetType;

class QBackgroundSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QBackgroundSheetType();
    ~QBackgroundSheetType();

    QString getValueText();
    QIcon   getValueIcon();

    QString getStyleSheetValue();

    void toXml(XmlNode * xml);
    void fromXml(XmlNode *xml);
    bool equal(const QVariant &value);
protected:
    QBrushSheetType *m_brush;
};

#endif // QBACKGROUNDSHEETTYPE_H
