#ifndef QENUMSHEETTYPE_H
#define QENUMSHEETTYPE_H

#include "qabstractsheettype.h"

class XmlNode;

class QEnumSheetType: public QAbstractSheetType
{
public:
    QEnumSheetType(QAbstractSheetType * parent = NULL);
    ~QEnumSheetType();

    QString getValueText();

    void    fromXml(XmlNode * xml);
    void    toXml(XmlNode * xml);

    QStringList getValueList();
protected:
    void    parserProperty(XmlNode *xml);
protected:
    QStringList     m_valueList;
};

#endif // QENUMSHEETTYPE_H
