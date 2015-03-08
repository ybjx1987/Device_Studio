#ifndef QBORDERSHEETTYPE_H
#define QBORDERSHEETTYPE_H

#include "qbrushsheettype.h"

class XmlNode;

class QBorderSheetType : public QBrushSheetType
{
    Q_OBJECT
public:
    Q_INVOKABLE QBorderSheetType();
    ~QBorderSheetType();

    QString getValueText();

    QString getStyleSheet();


    virtual bool    toXml(XmlNode * xml);
    virtual bool    fromXml(XmlNode * xml);

    QStringList     getStyleList();

    void        setBorderWidth(int width);
    int         getBorderWidth();

    void        setBorderStyle(const QString &style);
    QString     getBorderStyle();
protected:
    QString     m_borderStyle;
    int         m_borderWidth;
};

#endif // QBORDERSHEETTYPE_H
