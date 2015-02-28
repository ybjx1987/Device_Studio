#include "qfloatpropertyeditor.h"

#include "../../../kernel/property/qabstractproperty.h"

#include <QVBoxLayout>

QFloatPropertyEditor::QFloatPropertyEditor(QAbstractProperty* property):
    QAbstractPropertyEditor(property),
    m_spinBox(new QDoubleSpinBox)
{
    QVBoxLayout *v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_spinBox);
    setLayout(v);
    connect(m_spinBox,SIGNAL(valueChanged(double)),this,SLOT(edit()));

    float minValue = m_property->property("minValue").toFloat();
    float maxValue = m_property->property("maxValue").toFloat();
    if(minValue == maxValue && minValue == 0)
    {
        minValue = 0;
        maxValue = 9999.0;
    }
    m_spinBox->setRange(minValue,maxValue);

    m_spinBox->setValue(m_property->getValue().toFloat());
}

void QFloatPropertyEditor::edit()
{
    emit valueChanged(m_spinBox->value());
}

void QFloatPropertyEditor::propertyValueChanged()
{
    m_spinBox->setValue(m_property->getValue().toFloat());
}
