#ifndef QFONTPROPERTY_H
#define QFONTPROPERTY_H

#include "qabstractproperty.h"

class QEnumProperty;
class QIntProperty;
class QBoolProperty;

class QFontProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    QFontProperty(QAbstractProperty * parent = NULL);

    QString         getValueText();
    QIcon           getValueIcon();

    void            setValue(const QVariant &value);
    void            updateValue();
protected:
    void            makeValue(XmlNode *xml);
    void            writeValue(XmlNode *xml);
protected:
    QEnumProperty   *m_family;
    QIntProperty    *m_pointSize;
    QBoolProperty   *m_bold;
    QBoolProperty   *m_italic;
    QBoolProperty   *m_underline;
    QBoolProperty   *m_strikeout;
};

#endif // QFONTPROPERTY_H
