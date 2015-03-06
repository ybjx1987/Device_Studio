#include "qnewstylesheetgroupdialog.h"
#include "ui_qnewstylesheetgroupdialog.h"

#include "../../../libs/platform/qvalidatoredit.h"

QNewStyleSheetGroupDialog::QNewStyleSheetGroupDialog(const QStringList &list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewStyleSheetGroupDialog),
    m_nameEdit(new QValidatorEdit)
{
    ui->setupUi(this);
    setProperty("no-ManhattanStyle",true);
    ui->horizontalLayout_2->insertWidget(1,m_nameEdit,1);
    m_nameEdit->setIntermediateList(list);
}

QNewStyleSheetGroupDialog::~QNewStyleSheetGroupDialog()
{
    delete ui;
}

void QNewStyleSheetGroupDialog::on_okBtn_clicked()
{
    m_name = m_nameEdit->value();
    if(m_name == "")
    {
        return;
    }
    close();
}

void QNewStyleSheetGroupDialog::on_cancelBtn_clicked()
{
    close();
}

QString QNewStyleSheetGroupDialog::getName()
{
    return m_name;
}
