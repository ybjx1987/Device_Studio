#include "qintpropertyeditor.h"

#include "../../../kernel/property/qabstractproperty.h"

#include <QVBoxLayout>

QIntPropertyEditor::QIntPropertyEditor(QAbstractProperty* property):
    QAbstractPropertyEditor(property),
    m_spinBox(new QSpinBox)
{
    QVBoxLayout *v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_spinBox);
    setLayout(v);
    connect(m_spinBox,SIGNAL(valueChanged(int)),this,SLOT(edit()));

    int minValue = m_property->property("minValue").toInt();
    int maxValue = m_property->property("maxValue").toInt();
    if(minValue == maxValue && minValue == 0)
    {
        minValue = 0;
        maxValue = 9999;
    }
    m_spinBox->setRange(minValue,maxValue);

    m_spinBox->setValue(m_property->getValue().toInt());
}

void QIntPropertyEditor::edit()
{
    emit valueChanged(m_spinBox->value());
}

void QIntPropertyEditor::propertyValueChanged()
{
    m_spinBox->setValue(m_property->getValue().toInt());
}
