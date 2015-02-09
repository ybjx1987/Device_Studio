#include "qnewprojectdialog.h"
#include "ui_qnewprojectdialog.h"

QNewProjectDialog::QNewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewProjectDialog)
{
    ui->setupUi(this);
}

QNewProjectDialog::~QNewProjectDialog()
{
    delete ui;
}
