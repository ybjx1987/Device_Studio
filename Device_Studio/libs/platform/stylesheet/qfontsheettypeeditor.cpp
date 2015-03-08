#include "qfontsheettypeeditor.h"

#include "../../kernel/qvarianttype.h"
#include "../../kernel/stylesheet/type/qabstractsheettype.h"
#include "../stylehelper.h"

#include <QHBoxLayout>
#include <QFontDatabase>
static QStringList g_fontName;

QFontSheetTypeEditor::QFontSheetTypeEditor(QAbstractSheetType * property,
                                           QWidget * parent):
    QAbstractSheetPropertyEditor(property,parent),
    m_nameCombo(new QComboBox),
    m_styleCombo(new QComboBox),
    m_sizeEditor(new QSpinBox)
{
    m_nameCombo->setProperty("no-ManhattanStyle",true);
    m_styleCombo->setProperty("no-ManhattanStyle",true);
    m_sizeEditor->setProperty("no-ManhattanStyle",true);
    m_sizeEditor->setAttribute(Qt::WA_Hover);
    m_sizeEditor->setFixedHeight(StyleHelper::navigationWidgetHeight() - 4);
    static QFontDatabase data;
    g_fontName = data.families();
    QHBoxLayout * hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(5);

    hb->addWidget(m_styleCombo);
    hb->addWidget(m_sizeEditor);
    hb->addWidget(m_nameCombo);
    hb->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,
                                      QSizePolicy::Expanding));

    QStringList styles;
    styles<<"normal"<<"italic";
    m_styleCombo->addItems(styles);
    m_nameCombo->addItems(g_fontName);
    m_sizeEditor->setSuffix(" px");
    m_sizeEditor->setRange(0,255);


    setLayout(hb);

    propertyChanged();

    connect(m_nameCombo,SIGNAL(currentIndexChanged(int)),
            this,SLOT(propertyEdited()));
    connect(m_styleCombo,SIGNAL(currentIndexChanged(int)),
            this,SLOT(propertyEdited()));
    connect(m_sizeEditor,SIGNAL(valueChanged(int)),
            this,SLOT(propertyEdited()));
}

QFontSheetTypeEditor::~QFontSheetTypeEditor()
{

}

void QFontSheetTypeEditor::propertyChanged()
{
    if(m_property->getValue().isValid())
    {
        QStringList styles;
        styles<<"normal"<<"italic";
        tagFontSheetType value = m_property->getValue().value<tagFontSheetType>();
        if(!styles.contains(value.m_style))
        {
            m_styleCombo->setCurrentIndex(-1);
        }
        else
        {
            m_styleCombo->setCurrentText(value.m_style);
        }

        if(value.m_size > 0)
        {
            m_sizeEditor->setValue(value.m_size);
        }

        if(g_fontName.contains(value.m_name))
        {
            m_nameCombo->setCurrentText(value.m_name);
        }
        else
        {
            m_nameCombo->setCurrentIndex(-1);
        }
    }
    else
    {
        m_nameCombo->setCurrentIndex(-1);
        m_styleCombo->setCurrentIndex(-1);
        m_sizeEditor->setValue(0);
    }
}

void QFontSheetTypeEditor::propertyEdited()
{
    tagFontSheetType value;
    value.m_name = m_nameCombo->currentText();
    value.m_style = m_styleCombo->currentText();
    value.m_size = m_sizeEditor->value();

    if(value.m_name == "" && value.m_size <=0 && value.m_style == "")
    {
        m_property->setValue(QVariant());
    }
    else
    {
        m_property->setValue(QVariant::fromValue<tagFontSheetType>(value));
    }
}
