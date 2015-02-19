#include "qdellanguagedialog.h"
#include "ui_qdellanguagedialog.h"

#include "../../../libs/platform/qbaselistview.h"

#include "../../../libs/kernel/language/qlanguagemanager.h"
#include "../../../libs/kernel/language/qlanguage.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/qlanguageid.h"

#include <QHeaderView>

QDelLanguageDialog::QDelLanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDelLanguageDialog),
    m_listview(new QBaseListView)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0,m_listview,1);

    m_listview->header()->hide();
    m_listview->setFrameStyle(QFrame::Box);

    QLanguageManager *manager = QSoftCore::getInstance()->getProject()
            ->getLanguageManager();

    foreach(QLanguage* language,manager->getLanguages())
    {
        QLanguageInfo info = QLanguageID::getLanguageInfo(language->getID());
        QTreeWidgetItem *item = new QTreeWidgetItem(m_listview);
        item->setText(0,info.m_name);
        item->setIcon(0,QIcon(info.m_icon));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setCheckState(0,Qt::Unchecked);
        m_ItemToLanguage.insert(item,language);
        m_languageToItem.insert(language,item);
    }

    connect(m_listview,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(clicked(QTreeWidgetItem*)));
}

QDelLanguageDialog::~QDelLanguageDialog()
{
    delete ui;
}

void QDelLanguageDialog::clicked(QTreeWidgetItem *item)
{
    if(item->checkState(0) == Qt::Checked)
    {
        item->setCheckState(0,Qt::Unchecked);
    }
    else
    {
        item->setCheckState(0,Qt::Checked);
    }
}

void QDelLanguageDialog::on_cancelBtn_clicked()
{
    close();
}

void QDelLanguageDialog::on_okBtn_clicked()
{
    QMapIterator<QTreeWidgetItem*,QLanguage*> it(m_ItemToLanguage);

    QLanguageManager * manager = QSoftCore::getInstance()->getProject()->getLanguageManager();

    while(it.hasNext())
    {
        it.next();
        if(it.key()->checkState(0) == Qt::Checked)
        {
            manager->removeLanguage(it.value());
        }
    }

    close();
}
