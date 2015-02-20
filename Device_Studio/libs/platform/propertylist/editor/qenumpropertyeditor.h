#ifndef QENUMPROPERTYEDITOR_H
#define QENUMPROPERTYEDITOR_H

#include "qabstractpropertyeditor.h"

#include <QComboBox>

class PLATFORM_EXPORT QEnumPropertyEditor : public QAbstractPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QEnumPropertyEditor(QAbstractProperty * property);
public slots:
    void    edit();
protected:
    void    propertyValueChanged();

protected:
    QComboBox   *m_comboBox;
};

#endif // QENUMPROPERTYEDITOR_H
