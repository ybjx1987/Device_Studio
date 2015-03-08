#include "qbordersheettypeeditor.h"

#include "../../kernel/stylesheet/type/qbordersheettype.h"

#include <QHBoxLayout>

QBorderSheetTypeEditor::QBorderSheetTypeEditor(QAbstractSheetType * property,
                                               QWidget * parent):
        QBrushSheetTypeEditor(property,parent),
        m_borderWidth(new QSpinBox),
        m_borderStyle(new QComboBox)
{
    QHBoxLayout *hb = (QHBoxLayout*)layout();

    hb->insertWidget(0,m_borderWidth);
    hb->insertWidget(1,m_borderStyle);

    QBorderSheetType * borderPro = (QBorderSheetType*)property;

    m_borderStyle->addItems(borderPro->getStyleList());
    if(borderPro->getBorderStyle() != "")
    {
        m_borderStyle->setCurrentText(borderPro->getBorderStyle());
    }
    else
    {
        m_borderStyle->setCurrentIndex(-1);
    }
    m_borderWidth->setValue(borderPro->getBorderWidth());
    m_borderWidth->setSuffix("px");
    m_borderWidth->setFixedHeight(20);
    m_borderWidth->setRange(0,1000);

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
    QBorderSheetType * borderPro = (QBorderSheetType*)m_property;
    borderPro->setBorderWidth(m_borderWidth->value());
}

void QBorderSheetTypeEditor::styleChanged()
{
    QBorderSheetType * borderPro = (QBorderSheetType*)m_property;
    borderPro->setBorderStyle(m_borderStyle->currentText());
}
