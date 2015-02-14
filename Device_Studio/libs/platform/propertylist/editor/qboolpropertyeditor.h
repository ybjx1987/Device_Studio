#ifndef QBOOLPROPERTYEDITOR_H
#define QBOOLPROPERTYEDITOR_H

#include "qbasiceditor.h"

class QBoolPropertyEditor : public QBasicEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QBoolPropertyEditor(QAbstractProperty* property);

protected:
    void    mouseDoubleClickEvent(QMouseEvent * e);
};

#endif // QBOOLPROPERTYEDITOR_H
