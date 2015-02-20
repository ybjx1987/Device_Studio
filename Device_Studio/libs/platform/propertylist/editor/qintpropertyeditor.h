#ifndef QINTPROPERTYEDITOR_H
#define QINTPROPERTYEDITOR_H

#include "qabstractpropertyeditor.h"

#include <QSpinBox>

class PLATFORM_EXPORT QIntPropertyEditor : public QAbstractPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QIntPropertyEditor(QAbstractProperty* property);
protected slots:
    void    edit();
protected:
    void propertyValueChanged();
protected:
    QSpinBox    *m_spinBox;
};

#endif // QINTPROPERTYEDITOR_H
