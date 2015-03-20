#include "qbrusheditor.h"

#include "../../../libs/kernel/qvarianttype.h"
#include "../../../libs/kernel/stylesheet/type/qabstractsheettype.h"
#include "../../../libs/gradienteditor/qtgradientdialog.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QVariant>
#include <QColorDialog>
#include <QPixmap>
#include <QPainter>

QBrushEditor::QBrushEditor(QAbstractSheetType * property,QWidget *parent) :
    QWidget(parent),
    m_property(property),
    m_iconLabel(new QLabel),
    m_textLabel(new QLabel),
    m_editButton(new QToolButton)
{
    setProperty("no-ManhattanStyle",true);
    m_iconLabel->setFixedSize(16,16);

    QHBoxLayout *hb = new QHBoxLayout;
    hb->setContentsMargins(10,0,10,0);
    hb->setSpacing(5);

    hb->addWidget(m_editButton);
    hb->addWidget(m_iconLabel);
    hb->addWidget(m_textLabel,1);

    m_editButton->setFixedHeight(20);
    m_editButton->setPopupMode(QToolButton::MenuButtonPopup);

    setLayout(hb);

    QMenu * menu = new QMenu;
    m_editButton->setDefaultAction(menu->addAction(tr("Edited Color"),this,SLOT(editColor())));
    menu->addAction(tr("Edited Gradient"),this,SLOT(editGradient()));
    m_editButton->setMenu(menu);
    updateValue();
}

QBrushEditor::~QBrushEditor()
{

}

void QBrushEditor::editColor()
{
    tagBrushSheetType value = m_property->getValue().value<tagBrushSheetType>();

    QColor c;

    if(value.m_type == "Color")
    {
        c = value.m_value.value<QColor>();
        if(value.m_alpha != "true")
        {
            c.setAlpha(255);
        }
    }

    QColor color = QColorDialog::getColor(c,this,tr("Edit Color"),QColorDialog::ShowAlphaChannel);

    if(color.isValid())
    {
        value.m_type = "Color";
        value.m_value = QVariant::fromValue<QColor>(color);
        if(color.alpha() != 255)
        {
            value.m_alpha = "true";
        }
        else
        {
            value.m_alpha = "false";
        }
        QVariant v = QVariant::fromValue<tagBrushSheetType>(value);
        emit valueChanged(v);
        updateValue();
    }
}

void QBrushEditor::editGradient()
{
    tagBrushSheetType value = m_property->getValue().value<tagBrushSheetType>();

    QGradient g;

    if(value.m_type == "Gradient")
    {
        g = value.m_value.value<QGradient>();
    }
    bool ok;
    g = QtGradientDialog::getGradient(&ok,g,this,tr("Edit Gradient"));
    if(ok)
    {
        value.m_type = "Gradient";
        value.m_alpha = "false";
        value.m_value = QVariant::fromValue<QGradient>(g);
        QVariant v = QVariant::fromValue<tagBrushSheetType>(value);
        emit valueChanged(v);
        updateValue();
    }
}

void QBrushEditor::updateValue()
{
    m_iconLabel->setPixmap(m_property->getValueIcon().pixmap(QSize(16,16)));
    m_textLabel->setText(m_property->getValueText());
}
