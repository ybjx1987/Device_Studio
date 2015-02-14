#include "qbytearrayeditor.h"

#include "../../../kernel/property/qabstractproperty.h"

#include <QHBoxLayout>

QByteArrayEditor::QByteArrayEditor(QAbstractProperty* property):
    QAbstractPropertyEditor(property),
    m_lineEdit(new QValidatorEdit(".*"))
{
    QHBoxLayout * h= new QHBoxLayout;
    h->setMargin(0);
    h->setSpacing(0);
    h->addWidget(m_lineEdit);
    setLayout(h);

    m_lineEdit->setText(property->getValue().toString());

    connect(m_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(edit()));
}

void QByteArrayEditor::edit()
{
    emit valueChanged(m_lineEdit->text());
}


