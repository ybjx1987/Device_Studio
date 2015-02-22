#include "qstringeditordialog.h"
#include "ui_qstringeditordialog.h"


QStringEditorDialog::QStringEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QStringEditorDialog)
{
    ui->setupUi(this);
}

QStringEditorDialog::~QStringEditorDialog()
{
    delete ui;
}

void QStringEditorDialog::on_okBtn_clicked()
{
    close();
}

void QStringEditorDialog::on_cancelBtn_clicked()
{
    close();
}
