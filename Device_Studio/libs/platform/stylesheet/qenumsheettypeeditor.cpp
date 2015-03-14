#include "qenumsheettypeeditor.h"

#include "../../kernel/stylesheet/type/qenumsheettype.h"

#include <QHBoxLayout>

QEnumSheetTypeEditor::QEnumSheetTypeEditor(QAbstractSheetType * property,
                                           QWidget * parent):
    QAbstractSheetPropertyEditor(property,parent),
    m_combo(new QComboBox)
{
    setProperty("no-ManhattanStyle",true);
    QEnumSheetType *etype = (QEnumSheetType*)m_property;

    QHBoxLayout * hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(0);
    hb->addWidget(m_combo);
    setLayout(hb);

    m_combo->addItems(etype->getValueList());
    if(etype->getValueList().contains(etype->getValue().toString()))
    {
        m_combo->setCurrentText(etype->getValue().toString());
    }
    else
    {
        m_combo->setCurrentIndex(-1);
    }
    connect(m_combo,SIGNAL(currentIndexChanged(int)),
            this,SLOT(propertyEdited()));
}

QEnumSheetTypeEditor::~QEnumSheetTypeEditor()
{

}

void QEnumSheetTypeEditor::propertyEdited()
{
    m_property->setValue(m_combo->currentText());
}

void QEnumSheetTypeEditor::propertyChanged()
{
    m_combo->setCurrentText(m_property->getValue().toString());
}
