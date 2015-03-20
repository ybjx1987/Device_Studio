#include "qbordersheettypeeditor.h"

#include "qbrusheditor.h"

#include "../../kernel/stylesheet/type/qbordersheettype.h"
#include "../../kernel/stylesheet/type/qenumsheettype.h"
#include "../../kernel/stylesheet/type/qbrushsheettype.h"
#include "../../kernel/qvarianttype.h"

#include <QHBoxLayout>

QBorderSheetTypeEditor::QBorderSheetTypeEditor(QAbstractSheetType * property,
                                               QWidget * parent):
        QAbstractSheetPropertyEditor(property,parent),
        m_borderWidth(new QSpinBox),
        m_borderStyle(new QComboBox)
{
    setProperty("no-ManhattanStyle",true);

    QBorderSheetType * bp = (QBorderSheetType*)m_property;

    m_brushEditor = new QBrushEditor(bp->getBorderBrushProperty());

    QHBoxLayout * hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(0);
    hb->addWidget(m_borderWidth);
    hb->addWidget(m_borderStyle);
    hb->addWidget(m_brushEditor);
    setLayout(hb);

    m_borderStyle->addItems(bp->getBorderStyleProperty()->getValueList());
    connect(m_borderWidth,SIGNAL(valueChanged(int)),
            this,SLOT(widthChanged()));
    connect(m_borderStyle,SIGNAL(currentIndexChanged(int)),
            this,SLOT(styleChanged()));
    connect(m_brushEditor,SIGNAL(valueChanged(QVariant)),
            this,SLOT(brushChanged(QVariant)));

    tagBorderSheetType value = m_property->getValue().value<tagBorderSheetType>();
    if(value.m_borderStyle != "")
    {
        m_borderStyle->setCurrentText(value.m_borderStyle);
    }
    else
    {
        m_borderStyle->setCurrentIndex(-1);
    }
    m_borderWidth->setValue(value.m_borderWidth);
    m_brushEditor->updateValue();
}

QBorderSheetTypeEditor::~QBorderSheetTypeEditor()
{

}

void QBorderSheetTypeEditor::widthChanged()
{
    tagBorderSheetType value = m_property->getValue().value<tagBorderSheetType>();
    value.m_borderWidth = m_borderWidth->value();
    m_property->setValue(QVariant::fromValue<tagBorderSheetType>(value));
}

void QBorderSheetTypeEditor::styleChanged()
{
    tagBorderSheetType value = m_property->getValue().value<tagBorderSheetType>();
    value.m_borderStyle = m_borderStyle->currentText();
    m_property->setValue(QVariant::fromValue<tagBorderSheetType>(value));

}

void QBorderSheetTypeEditor::propertyChanged()
{
    tagBorderSheetType value = m_property->getValue().value<tagBorderSheetType>();
    if(value.m_borderStyle != "")
    {
        m_borderStyle->setCurrentText(value.m_borderStyle);
    }
    else
    {
        m_borderStyle->setCurrentIndex(-1);
    }
    m_borderWidth->setValue(value.m_borderWidth);
    m_brushEditor->updateValue();
}

void QBorderSheetTypeEditor::brushChanged(const QVariant &value)
{
    tagBorderSheetType v = m_property->getValue().value<tagBorderSheetType>();
    v.m_borderBrush = value.value<tagBrushSheetType>();
    m_property->setValue(QVariant::fromValue<tagBorderSheetType>(v));
}
