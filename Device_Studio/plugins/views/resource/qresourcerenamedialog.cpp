#include "qresourcerenamedialog.h"
#include "ui_qresourcerenamedialog.h"

#include "../../../libs/platform/qvalidatoredit.h"

QResourceRenameDialog::QResourceRenameDialog(const QString &oldName,
                                             const QStringList &list,
                                             QWidget *parent):
    QDialog(parent),
    ui(new Ui::QResourceRenameDialog),
    m_nameEdit(new QValidatorEdit(".*")),
    m_ret(0)
{
    ui->setupUi(this);
    ui->horizontalLayout->insertWidget(0,m_nameEdit,0);

    int index = oldName.lastIndexOf(".");
    m_nameEdit->setValue(oldName.left(index));
    m_nameEdit->selectAll();

    QString ex = oldName.mid(index);
    QStringList l;
    foreach(QString str,list)
    {
        if(str.endsWith(ex))
        {
            l.append(str.left(str.size()-ex.size()));
        }
    }
    m_nameEdit->setIntermediateList(l);
    ui->label->setText(ex.mid(1));
}

QResourceRenameDialog::~QResourceRenameDialog()
{
    delete ui;
}

void QResourceRenameDialog::on_pushButton_2_clicked()
{
    if(m_nameEdit->value() == "")
    {
        return;
    }
    m_ret = 1;
    close();
}

int QResourceRenameDialog::getRet()
{
    return m_ret;
}

QString QResourceRenameDialog::getNewName()
{
    return m_nameEdit->value()+"."+ui->label->text();
}

void QResourceRenameDialog::on_pushButton_clicked()
{
    close();
}
