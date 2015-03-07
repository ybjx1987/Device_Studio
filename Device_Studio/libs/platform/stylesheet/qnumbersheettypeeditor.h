#ifndef QNUMBERSHEETTYPEEDITOR_H
#define QNUMBERSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>

class QNumberSheetTypeEditor : public QAbstractSheetPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QNumberSheetTypeEditor(QAbstractSheetType * property,QWidget * parent = NULL);
    ~QNumberSheetTypeEditor();

protected:
    void    propertyChanged();
protected slots:
    void    propertyEdited();
    void    typeChanged();
protected:
    QComboBox       *m_typeComboBox;
    QSpinBox        *m_intValue;
    QDoubleSpinBox  *m_floatValue;
};

#endif // QNUMBERSHEETTYPEEDITOR_H
