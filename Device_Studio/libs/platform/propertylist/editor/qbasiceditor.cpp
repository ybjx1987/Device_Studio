#include "qbasiceditor.h"

#include "../../../kernel/property/qabstractproperty.h"

#include <QHBoxLayout>

QBasicEditor::QBasicEditor(QAbstractProperty *property):
    QAbstractPropertyEditor(property),
    m_icon(new QLabel(this)),
    m_text(new QLabel(this))
{
    this->setFocusPolicy(Qt::StrongFocus);
    m_text->setContentsMargins(0,1,0,0);

    propertyValueChanged();

    QHBoxLayout *l=new QHBoxLayout;
    this->setLayout(l);
    l->setContentsMargins(3,2,3,2);
    l->setSpacing(3);
    l->addWidget(m_icon);
    l->addWidget(m_text);
    connect(m_property,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(propertyValueChanged()));
}

void QBasicEditor::propertyValueChanged()
{
    m_text->setText(m_property->getValueText());
    QIcon icon=m_property->getValueIcon();
    if(icon.isNull())
    {
        m_icon->setVisible(false);
    }
    else
    {
        QPixmap pix=icon.pixmap(QSize(16,16));
        m_icon->setFixedSize(16,16);
        m_icon->setPixmap(pix);
    }
}
