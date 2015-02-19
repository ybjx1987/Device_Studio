#include "qnewlanguagedialog.h"
#include "ui_qnewlanguagedialog.h"

#include "../../../libs/kernel/xmlnode.h"
#include "../../../libs/platform/qlanguageid.h"

#include <QFile>

QNewLanguageDialog::QNewLanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewLanguageDialog)
{
    ui->setupUi(this);
    setWindowTitle("New Language");

    m_languageInfos = QLanguageID::getLanguageInfos();

    foreach(QLanguageInfo info,m_languageInfos)
    {
        ui->comboBox->addItem(QIcon(info.m_icon),info.m_name);
    }
}

QNewLanguageDialog::~QNewLanguageDialog()
{
    delete ui;
}

QString QNewLanguageDialog::getLanguageID()
{
    return m_id;
}

void QNewLanguageDialog::on_pushButton_2_clicked()
{
    QLanguageInfo info= m_languageInfos.at(ui->comboBox->currentIndex());
    m_id = info.m_id;
    close();
}

void QNewLanguageDialog::on_pushButton_clicked()
{
    close();
}
