#ifndef QBRUSHSHEETTYPE_H
#define QBRUSHSHEETTYPE_H

#include "qabstractsheettype.h"

#include <QGradient>

class XmlNode;

class QBrushSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QBrushSheetType(QAbstractSheetType * parent = NULL);
    ~QBrushSheetType();

    QString getValueText();
    QIcon getValueIcon();

    QString getStyleSheetValue();


    virtual void    toXml(XmlNode * xml);
    virtual void    fromXml(XmlNode * xml);

    virtual bool    equal(const QVariant & value);
protected:
    QStringList styleSheetParameters(const QGradient &gradient);
    QStringList styleSheetStops(const QGradient &gradient);
    QString styleSheetFillName(const QGradient &gradient);
    QString styleSheetCode(const QGradient &gradient);
};

#endif // QBRUSHSHEETTYPE_H
