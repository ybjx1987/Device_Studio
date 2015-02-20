#include "qlineeditdialog.h"
#include "ui_qlineeditdialog.h"

QLineEditDialog::QLineEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QLineEditDialog),
    m_ret(0)
{
    ui->setupUi(this);
}

QLineEditDialog::~QLineEditDialog()
{
    delete ui;
}

void QLineEditDialog::setText(const QString &text)
{
    ui->textEdit->setPlainText(text);
}

QString QLineEditDialog::getText()
{
    return ui->textEdit->toPlainText();
}

int QLineEditDialog::getRet()
{
    return m_ret;
}

void QLineEditDialog::on_pushButton_clicked()
{
    m_ret =1;
    close();
}

void QLineEditDialog::on_pushButton_2_clicked()
{
    m_ret = 0;
    close();
}
