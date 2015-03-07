#include "qnumbersheettypeeditor.h"

#include "../../kernel/stylesheet/type/qabstractsheettype.h"
#include "../../kernel/stylesheet/type/qnumbersheettype.h"

#include <QHBoxLayout>

QNumberSheetTypeEditor::QNumberSheetTypeEditor(QAbstractSheetType * property,
                                               QWidget * parent):
    QAbstractSheetPropertyEditor(property,parent),
    m_typeComboBox(new QComboBox),
    m_intValue(new QSpinBox),
    m_floatValue(new QDoubleSpinBox)
{
    QHBoxLayout *hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(10);
    hb->addWidget(m_typeComboBox);
    hb->addWidget(m_intValue,1);
    hb->addWidget(m_floatValue,1);

    setLayout(hb);
    m_typeComboBox->addItems(QStringList()<<"Integer"<<"Float");
    QNumberSheetType *ntype = (QNumberSheetType*)m_property;
    m_typeComboBox->setCurrentText(ntype->getType());
    typeChanged();
    connect(m_intValue,SIGNAL(valueChanged(int)),this,SLOT(propertyEdited()));
    connect(m_floatValue,SIGNAL(valueChanged(double)),this,SLOT(propertyEdited()));
    connect(m_typeComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(typeChanged()));

    m_intValue->setRange(-9999999,9999999);
    m_floatValue->setRange(-99999999,99999999);
    m_floatValue->setDecimals(6);
}

QNumberSheetTypeEditor::~QNumberSheetTypeEditor()
{

}

void QNumberSheetTypeEditor::propertyChanged()
{
    if(m_typeComboBox->currentText() == "Integer")
    {
        m_intValue->setValue(m_property->getValue().toInt());
    }
    else
    {
        m_floatValue->setValue(m_property->getValue().toFloat());
    }
}

void QNumberSheetTypeEditor::propertyEdited()
{
    if(m_typeComboBox->currentText() == "Integer")
    {
        m_property->setValue(m_intValue->value());
    }
    else
    {
        m_property->setValue(m_floatValue->value());
    }
}

void QNumberSheetTypeEditor::typeChanged()
{
    if(m_typeComboBox->currentText() == "Integer")
    {
        m_intValue->setVisible(true);
        m_floatValue->setValue(false);
        m_intValue->setValue(m_property->getValue().toInt());
    }
    else
    {
        m_intValue->setVisible(false);
        m_floatValue->setValue(true);
        m_floatValue->setValue(m_property->getValue().toInt());
    }
    QNumberSheetType *ntype = (QNumberSheetType*)m_property;
    ntype->setType(m_typeComboBox->currentText());
}
