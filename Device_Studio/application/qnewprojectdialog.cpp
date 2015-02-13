#include "qnewprojectdialog.h"
#include "ui_qnewprojectdialog.h"

#include "../libs/platform/qvalidatoredit.h"

#include <QFileDialog>

QNewProjectDialog::QNewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewProjectDialog),
    m_projectName(new QValidatorEdit())
{
    ui->setupUi(this);

    ui->okBtn->setFocus();
    ui->gridLayout_2->addWidget(m_projectName,1,1);
}

QNewProjectDialog::~QNewProjectDialog()
{
    delete ui;
}

void QNewProjectDialog::on_fileBtn_clicked()
{
    QString path = ui->pathEdit->text();

    if(path == "")
    {
        path = QDir::currentPath();
    }

    path = QFileDialog::getExistingDirectory(this,tr("Project Path"),path);

    if(path != "")
    {
        ui->pathEdit->setText(path);
    }
}

void QNewProjectDialog::on_okBtn_clicked()
{
    QString name = m_projectName->value();
    QString path = ui->pathEdit->text();

    if(name == "" || path == "")
    {
        return ;
    }
    m_name = name;
    m_path = path;
    close();
}

void QNewProjectDialog::on_cancelBtn_clicked()
{
    close();
}

QString QNewProjectDialog::getName()
{
    return m_name;
}

QString QNewProjectDialog::getPath()
{
    return m_path;
}
