#include "qnewlanguagedialog.h"
#include "ui_qnewlanguagedialog.h"

#include "../../../libs/kernel/xmlnode.h"

#include <QFile>

QNewLanguageDialog::QNewLanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewLanguageDialog)
{
    ui->setupUi(this);
    setWindowTitle("New Language");
    load();
}

QNewLanguageDialog::~QNewLanguageDialog()
{
    delete ui;
}

void QNewLanguageDialog::load()
{
    QFile file(":/inner/images/languages/translation.xml");

    if(!file.exists())
    {
        return;
    }

    if(!file.open(QFile::ReadOnly))
    {
        return;
    }

    QString str = file.readAll();

    XmlNode xml;
    if(!xml.load(str))
    {
        return;
    }

    if(xml.getTitle() != "Languages")
    {
        return;
    }

    QString name;

    foreach(XmlNode *obj,xml.getChildren())
    {
        LanguageInfo info;
        info.m_icon = ":/inner/images/languages/"+obj->getProperty("icon");
        info.m_id = obj->getProperty("id");
        info.m_name = obj->getProperty("name");
        m_languageInfos.append(info);
        ui->comboBox->addItem(QIcon(info.m_icon),info.m_name);
    }
}

LanguageInfo QNewLanguageDialog::getLanguageInfo()
{
    return m_languageInfo;
}

void QNewLanguageDialog::on_pushButton_2_clicked()
{
    m_languageInfo = m_languageInfos.at(ui->comboBox->currentIndex());
    close();
}

void QNewLanguageDialog::on_pushButton_clicked()
{
    close();
}
