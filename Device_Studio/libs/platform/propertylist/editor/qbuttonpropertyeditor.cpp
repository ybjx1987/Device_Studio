#include "qbuttonpropertyeditor.h"

#include <QToolButton>
#include <QLayout>

QButtonPropertyEditor::QButtonPropertyEditor(QAbstractProperty * property):
    QBasicEditor(property)
{
    QToolButton *m_button = new QToolButton(this);
    m_button->setText("...");
    m_button->setFixedSize(16,16);

    QLayout *layout = this->layout();
    layout->addWidget(m_button);

    connect(m_button,SIGNAL(clicked()),this,SLOT(buttonClicked()));
}

void QButtonPropertyEditor::buttonClicked()
{

}
