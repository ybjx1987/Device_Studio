#include "qbordersheettypeeditor.h"

#include "../../kernel/stylesheet/type/qbordersheettype.h"
#include "../../kernel/stylesheet/type/qenumsheettype.h"
#include "../../kernel/qvarianttype.h"

#include <QHBoxLayout>

QBorderSheetTypeEditor::QBorderSheetTypeEditor(QAbstractSheetType * property,
                                               QWidget * parent):
        QBrushSheetTypeEditor(property->getChildren().at(2),parent),
        m_borderWidth(new QSpinBox),
        m_borderStyle(new QComboBox),
        m_borderProperty(property)
{
    QHBoxLayout * hb = (QHBoxLayout*)layout();
    hb->insertWidget(0,m_borderWidth);
    hb->insertWidget(1,m_borderStyle);

    m_borderStyle->addItems(((QEnumSheetType*)property->getChildren().at(0))
                            ->getValueList());
    connect(m_borderWidth,SIGNAL(valueChanged(int)),
            this,SLOT(widthChanged()));
    connect(m_borderStyle,SIGNAL(currentIndexChanged(int)),
            this,SLOT(styleChanged()));
}

QBorderSheetTypeEditor::~QBorderSheetTypeEditor()
{

}

void QBorderSheetTypeEditor::widthChanged()
{
    tagBorderSheetType value = m_borderProperty->getValue().value<tagBorderSheetType>();
    value.m_borderWidth = m_borderWidth->value();
    m_borderProperty->setValue(QVariant::fromValue<tagBorderSheetType>(value));
}

void QBorderSheetTypeEditor::styleChanged()
{
    tagBorderSheetType value = m_borderProperty->getValue().value<tagBorderSheetType>();
    value.m_borderStyle = m_borderStyle->currentText();
    m_borderProperty->setValue(QVariant::fromValue<tagBorderSheetType>(value));

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
    QBrushSheetTypeEditor::propertyChanged();
}
