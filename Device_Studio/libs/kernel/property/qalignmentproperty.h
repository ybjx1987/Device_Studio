#ifndef QALIGNMENTPROPERTY_H
#define QALIGNMENTPROPERTY_H

#include "qabstractproperty.h"

class QEnumProperty;

class KERNEL_EXPORT QAlignmentProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    QAlignmentProperty(QAbstractProperty * parent = NULL);

    QString         getValueText();
    QIcon           getValueIcon();

    void            setValue(const QVariant &value);

protected:
    void            updateValue();
protected:
    void            makeValue(XmlNode *xml);
    void            writeValue(XmlNode *xml);
protected:
    QEnumProperty   *m_horizonta;
    QEnumProperty   *m_vertical;
};

#endif // QALIGNMENTPROPERTY_H
