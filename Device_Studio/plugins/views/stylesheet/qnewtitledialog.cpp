#include "qnewtitledialog.h"
#include "ui_qnewtitledialog.h"

QNewTitleDialog::QNewTitleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewTitleDialog)
{
    ui->setupUi(this);
}

QNewTitleDialog::~QNewTitleDialog()
{
    delete ui;
}
