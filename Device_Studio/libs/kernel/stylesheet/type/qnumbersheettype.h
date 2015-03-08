#ifndef QNUMBERSHEETTYPE_H
#define QNUMBERSHEETTYPE_H

#include "qabstractsheettype.h"

class QNumberSheetType : public QAbstractSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QNumberSheetType();
    ~QNumberSheetType();

    QString getValueText();

    QString getType();
    void    setType(const QString &type);

    bool    toXml(XmlNode *xml);
    bool    fromXml(XmlNode *xml);
protected:
    QString m_type;
};

#endif // QNUMBERSHEETTYPE_H
