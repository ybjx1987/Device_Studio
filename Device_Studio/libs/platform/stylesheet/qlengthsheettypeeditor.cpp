#include "qlengthsheettypeeditor.h"

#include <QHBoxLayout>

QLengthSheetTypeEditor::QLengthSheetTypeEditor(QAbstractSheetType * property,
                                               QWidget* parent):
    QNumberSheetTypeEditor(property,parent)
{
    m_typeComboBox->setVisible(false);
    m_floatValue->setVisible(false);
    QHBoxLayout *hb = (QHBoxLayout*)layout();
    hb->setMargin(0);
    hb->setSpacing(0);
}

QLengthSheetTypeEditor::~QLengthSheetTypeEditor()
{

}

