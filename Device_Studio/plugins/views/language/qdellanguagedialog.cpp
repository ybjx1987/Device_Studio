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
        m_ItemToLanguage.insert(item,language);
        m_languageToItem.insert(language,item);
    }
}

QDelLanguageDialog::~QDelLanguageDialog()
{
    delete ui;
}
