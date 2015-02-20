#include "qnewallitemdialog.h"
#include "ui_qnewallitemdialog.h"

#include <QMessageBox>

QNewAllItemDialog::QNewAllItemDialog(const QStringList &list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewAllItemDialog),
    m_keyEdit(new QValidatorEdit(".*"))
{
    ui->setupUi(this);
    m_keyEdit->setIntermediateList(list);
    ui->horizontalLayout->insertWidget(1,m_keyEdit,1);
}

QNewAllItemDialog::~QNewAllItemDialog()
{
    delete ui;
}

void QNewAllItemDialog::on_pushButton_clicked()
{
    m_key = m_keyEdit->value();
    if(m_key == "")
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("Keyword cann't been empty!"));
        return;
    }
    close();
}

void QNewAllItemDialog::on_pushButton_2_clicked()
{
    close();
}

QString QNewAllItemDialog::getKey()
{
    return m_key;
}
