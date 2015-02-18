#include "qenumpropertyeditor.h"

#include "../../../kernel/qvarianttype.h"
#include "../../../kernel/property/qabstractproperty.h"

#include <QVBoxLayout>

QEnumPropertyEditor::QEnumPropertyEditor(QAbstractProperty * property):
    QAbstractPropertyEditor(property),
    m_comboBox(new QComboBox)
{
    QVBoxLayout *v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_comboBox);
    setLayout(v);

    ComboItems items = property->property("items").value<ComboItems>();

    foreach(tagComboItem item,items)
    {
        m_comboBox->addItem(QIcon(item.m_icon),item.m_text);
    }

    propertyValueChanged();

    connect(m_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(edit()));
}

void QEnumPropertyEditor::edit()
{
    int index = m_comboBox->currentIndex();
    ComboItems items = m_property->property("items").value<ComboItems>();

    tagComboItem item = items.at(index);

    if(!m_property->equal(item.m_value))
    {
        emit valueChanged(item.m_value);
    }
}

void QEnumPropertyEditor::propertyValueChanged()
{
    ComboItems items = m_property->property("items").value<ComboItems>();

    int count = items.size();

    for(int i= 0;i<count;i++)
    {
        if(m_property->equal(items.at(i).m_value))
        {
            m_comboBox->setCurrentIndex(i);
            return;
        }
    }
}
