#ifndef QFLOATPROPERTYEDITOR_H
#define QFLOATPROPERTYEDITOR_H

#include "qabstractpropertyeditor.h"

#include <QDoubleSpinBox>

class PLATFORM_EXPORT QFloatPropertyEditor : public QAbstractPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QFloatPropertyEditor(QAbstractProperty* property);
protected slots:
    void    edit();
protected:
    void propertyValueChanged();
protected:
    QDoubleSpinBox    *m_spinBox;
};

#endif // QFLOATPROPERTYEDITOR_H
