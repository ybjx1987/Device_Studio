#ifndef QCURSORPROPERTY_H
#define QCURSORPROPERTY_H

#include "qenumproperty.h"

class XmlNode;

class KERNEL_EXPORT QCursorProperty : public QEnumProperty
{
    Q_OBJECT
public:
    QCursorProperty(QAbstractProperty* parent=0);

protected:
    void    makeValue(XmlNode *xml);
    void    writeValue(XmlNode *xml);
};

#endif // QCURSORPROPERTY_H
