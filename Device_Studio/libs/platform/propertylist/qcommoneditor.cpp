#include "qcommoneditor.h"

#include "../../kernel/property/qabstractproperty.h"

#include <QHBoxLayout>

QCommonEditor::QCommonEditor(QAbstractProperty *property, QWidget *parent):
    QWidget(parent),
    m_icon(new QLabel(this)),
    m_text(new QLabel(this)),
    m_property(property)
{
    setFocusPolicy(Qt::StrongFocus);
    m_text->setContentsMargins(0,1,0,0);
    m_text->setText(m_property->getValueText());
    QIcon icon = m_property->getValueIcon();
    if(icon.isNull())
    {
        m_icon->setVisible(false);
    }
    else
    {
        QPixmap pix = icon.pixmap(QSize(16,16));
        m_icon->setFixedSize(16,16);
        m_icon->setPixmap(pix);
    }

    QHBoxLayout *layout = new QHBoxLayout();
    setLayout(layout);
    layout->setContentsMargins(5,3,3,2);
    layout->setSpacing(0);
    layout->setSpacing(3);
    layout->addWidget(m_icon);
    layout->addWidget(m_text);
    connect(m_property,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(propertyChanged()));
}

void QCommonEditor::propertyChanged()
{
    m_text->setText(m_property->getValueText());
    QIcon icon = m_property->getValueIcon();
    if(icon.isNull())
    {
        m_icon->setVisible(false);
    }
    else
    {
        QPixmap pix = icon.pixmap(QSize(16,16));
        m_icon->setFixedSize(16,16);
        m_icon->setPixmap(pix);
    }
}
