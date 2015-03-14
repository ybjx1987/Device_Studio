#include "qnumbersheettypeeditor.h"

#include "../../../libs/kernel/stylesheet/type/qnumbersheettype.h"

#include <QHBoxLayout>

QNumberSheetTypeEditor::QNumberSheetTypeEditor(QAbstractSheetType * property,
                                               QWidget* parent):
    QAbstractSheetPropertyEditor(property,parent),
    m_valueEditor(new QSpinBox)
{
    QHBoxLayout *hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(0);
    hb->addWidget(m_valueEditor);

    QNumberSheetType * type = (QNumberSheetType*)m_property;
    m_valueEditor->setRange(type->getMinValue(),type->getMaxValue());
    setLayout(hb);

    connect(m_valueEditor,SIGNAL(valueChanged(int)),this,SLOT(valueEdited()));
}

QNumberSheetTypeEditor::~QNumberSheetTypeEditor()
{

}

void QNumberSheetTypeEditor::valueEdited()
{
    m_property->setValue(m_valueEditor->value());
}

