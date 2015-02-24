#include "qnewdatagroupdialog.h"
#include "ui_qnewdatagroupdialog.h"

#include "../../../libs/platform/qvalidatoredit.h"

#include <QMessageBox>

QNewDataGroupDialog::QNewDataGroupDialog(const QStringList & list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewDataGroupDialog),
    m_nameEdit(new QValidatorEdit)
{
    ui->setupUi(this);
    ui->horizontalLayout->insertWidget(1,m_nameEdit,1);
    m_nameEdit->setIntermediateList(list);
}

QNewDataGroupDialog::~QNewDataGroupDialog()
{
    delete ui;
}

void QNewDataGroupDialog::on_okBtn_clicked()
{
    m_name = m_nameEdit->value();

    if(m_name == "")
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("The group name cann't be empty!"));
        return;
    }

    close();
}

void QNewDataGroupDialog::on_cancelBtn_clicked()
{
    close();
}

QString QNewDataGroupDialog::getName()
{
    return m_name;
}
