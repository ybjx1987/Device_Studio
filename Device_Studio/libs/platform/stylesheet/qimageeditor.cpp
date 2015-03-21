#include "qimageeditor.h"

#include "qimageselectdialog.h"

#include "../../kernel/stylesheet/type/qabstractsheettype.h"
#include "../../kernel/resource/qresourcefile.h"

#include <QHBoxLayout>

QImageEditor::QImageEditor(QAbstractSheetType * property,QWidget *parent) :
    QWidget(parent),
    m_iconLabel(new QLabel),
    m_textLabel(new QLabel),
    m_editButton(new QToolButton),
    m_property(property)
{
    QHBoxLayout * hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(3);
    hb->addWidget(m_iconLabel);
    hb->addWidget(m_editButton);
    hb->addWidget(m_textLabel);
    m_editButton->setText("...");
    setLayout(hb);
    m_iconLabel->setFixedSize(16,16);
    m_editButton->setFixedSize(20,20);

    updateValue();

    connect(m_editButton,SIGNAL(clicked()),this,SLOT(editImage()));

}

QImageEditor::~QImageEditor()
{

}

void QImageEditor::updateValue()
{
    m_iconLabel->setPixmap(m_property->getValueIcon().pixmap(16,16));
    m_textLabel->setText(m_property->getValueText());
}

void QImageEditor::editImage()
{
    QImageSelectDialog dlg(this);

    dlg.exec();

    QResourceFile * file = dlg.getSelect();
    if(file != NULL)
    {
        emit valueChanged(file->getPath());
        updateValue();
    }
}
