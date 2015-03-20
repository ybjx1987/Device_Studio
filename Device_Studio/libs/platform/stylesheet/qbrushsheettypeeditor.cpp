#include "qbrushsheettypeeditor.h"

#include "qbrusheditor.h"

#include "../../kernel/stylesheet/type/qabstractsheettype.h"
#include "../../kernel/qvarianttype.h"
#include "../../gradienteditor/qtgradientdialog.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QColorDialog>

QBrushSheetTypeEditor::QBrushSheetTypeEditor(QAbstractSheetType * property,
                                             QWidget * parent):
      QAbstractSheetPropertyEditor(property,parent),
      m_brushEditor(new QBrushEditor(property))
{
    QHBoxLayout *hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(0);
    hb->addWidget(m_brushEditor);
    setLayout(hb);

    connect(m_brushEditor,SIGNAL(valueChanged(QVariant)),
            this,SLOT(valueChanged(QVariant)));
}

QBrushSheetTypeEditor::~QBrushSheetTypeEditor()
{

}

void QBrushSheetTypeEditor::propertyChanged()
{
    m_brushEditor->updateValue();
}

void QBrushSheetTypeEditor::valueChanged(const QVariant &value)
{
    m_property->setValue(value);
}
