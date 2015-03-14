#ifndef QNUMBERSHEETTYPE_H
#define QNUMBERSHEETTYPE_H

#include "qabstractsheettype.h"

class QNumberSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QNumberSheetType(QAbstractSheetType * parent = NULL);
    ~QNumberSheetType();

    QString getValueText();

    void    toXml(XmlNode *xml);
    void    fromXml(XmlNode *xml);

    int     getMinValue();
    int     getMaxValue();
protected:
    void    parserProperty(XmlNode *xml);
protected:
    int     m_minValue;
    int     m_maxValue;
};

#endif // QNUMBERSHEETTYPE_H
