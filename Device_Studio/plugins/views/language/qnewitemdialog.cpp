#include "qnewitemdialog.h"
#include "ui_qnewitemdialog.h"

#include <QMessageBox>

QNewItemDialog::QNewItemDialog(const QStringList &list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewItemDialog),
    m_keyEdit(new QValidatorEdit(".*"))
{
    ui->setupUi(this);
    m_keyEdit->setIntermediateList(list);
    ui->horizontalLayout->insertWidget(1,m_keyEdit,1);
    m_keyEdit->setFocus();
}

QNewItemDialog::~QNewItemDialog()
{
    delete ui;
}

void QNewItemDialog::on_okBtn_clicked()
{
    m_key = m_keyEdit->value();
    if(m_key=="")
    {
        QMessageBox::warning(this,tr("New Item"),
                             tr("Keywrod cann't been empty!"));
        return;
    }
    close();
}

void QNewItemDialog::on_cancelBtn_clicked()
{
    close();
}

QString QNewItemDialog::getKey()
{
    return m_key;
}
