#ifndef QRECTPROPERTY_H
#define QRECTPROPERTY_H

#include "qabstractproperty.h"

class QIntProperty;
class XmlNode;

class KERNEL_EXPORT QRectProperty: public QAbstractProperty
{
    Q_OBJECT
public:
    QRectProperty(QAbstractProperty * parent = NULL);

    QString     getValueText();
    QIcon       getValueIcon();

    void        setValue(const QVariant &value);

    QVariant    getValue();

    void        setSizeType(bool sizeType);
protected:
    void        makeValue(XmlNode *xml);
    void        writeValue(XmlNode *xml);

protected:
    void        updateValue();
protected:
    QIntProperty    *m_x;
    QIntProperty    *m_y;
    QIntProperty    *m_width;
    QIntProperty    *m_height;
};

#endif // QRECTPROPERTY_H
