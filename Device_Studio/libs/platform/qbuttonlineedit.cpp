#include "qbuttonlineedit.h"

#include "qlineeditdialog.h"

QButtonLineEdit::QButtonLineEdit(QWidget *parent) :
    QLineEdit(parent),
    m_button(new QPushButton(this))
{
    setContentsMargins(0,0,20,0);
    m_button->setFixedSize(16,16);
    m_button->setText("...");

    connect(m_button,SIGNAL(clicked()),this,SLOT(showDialog()));
}

QButtonLineEdit::~QButtonLineEdit()
{

}

void QButtonLineEdit::resizeEvent(QResizeEvent *e)
{
    int w = this->width();
    m_button->move(w-18,2);
    QLineEdit::resizeEvent(e);
}

void QButtonLineEdit::showDialog()
{
    QLineEditDialog dlg(this);
    dlg.setText(text());
    dlg.exec();
    if(dlg.getRet() == 1)
    {
        setText(dlg.getText());
    }
}
